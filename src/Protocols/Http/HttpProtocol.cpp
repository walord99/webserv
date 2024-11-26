/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpProtocol.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:36:44 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 18:10:14 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpProtocol.hpp"

HttpProtocol::HttpProtocol(void) : IProtocol(), _processed_content_lenght(0), _framing_state(HEADER), _proto_state(WAITING), _header_state(REQUEST_LINE), _content(NULL), _response_code(0), _discard(false)
{
	_read_buffer = new std::string();
	_read_buffer->reserve(8000);
}

HttpProtocol::~HttpProtocol(void)
{
	delete _read_buffer;
	if (_content != NULL)
		delete _content;
}

HttpProtocol::HttpProtocol(const HttpProtocol &other) : IProtocol()
{
	*this = other;
}

HttpProtocol &HttpProtocol::operator=(const HttpProtocol &other)
{
	if (this != &other)
	{
	}
	return *this;
}

IProtocol::processAction HttpProtocol::processInput(std::string &input)
{
	if (_framing_state == HEADER || _framing_state == TRAILING)
	{
		if (_read_buffer->size() + input.size() > 8000)
		{
			if (_header_state == REQUEST_LINE)
				defensiveParseRequestLine();
			else if (_header_state == HEADER_FIELDS || _framing_state == TRAILING)
				// defensiveParseField();
				;
			return IProtocol::CONTINUE;
		}
		*_read_buffer += input;
		while (_framing_state == HEADER && getLineLength(*_read_buffer) != -1)
		{
			if (_header_state == REQUEST_LINE)
				parseRequestLine();
			else if (_header_state == HEADER_FIELDS || _framing_state == TRAILING)
				parseFieldLine();
			_read_buffer->erase(0, getLineLength(*_read_buffer));
		}
	}
	else if (_framing_state == BODY)
	{
	}
	return IProtocol::CONTINUE;
}

IProtocol::outputAction HttpProtocol::output(std::string **out_loc)
{
	if (_proto_state == OUTPUT_READY)
	{
		if (_response_code == 400)
		{
			*out_loc = new std::string("HTTP/1.1 400 Bad Request\r\nServer: mine\r\nContent-Lenght: 0\r\n\r\n");
		}
		else
			*out_loc = new std::string("HTTP/1.1 404 Not Found\r\n\r\ncum\n\r\n\r\n");
		reset();
		return IProtocol::OVER;
	}
	else
		return IProtocol::NO_OUTPUT;
}

int HttpProtocol::getLineLength(std::string &input) const
{
	bool is_prev_CR = false;
	for (std::string::iterator i = input.begin(); i != input.end(); i++)
	{
		if (*i == '\r')
			is_prev_CR = true;
		else if (is_prev_CR && *i == '\n')
			return i - input.begin() + 1;
		else
			is_prev_CR = false;
	}
	return -1;
}

void HttpProtocol::reset(void)
{
	_framing_state = HttpProtocol::HEADER;
	_read_buffer->resize(0);
	_header_fields.clear();
	_trailing_fields.clear();
	_response_code = 0;
	_discard = false;
	_header_state = REQUEST_LINE;
	if (_content)
		delete _content;
	_processed_content_lenght = 0;
	_content_lenght = -1;
}

void HttpProtocol::parseRequestLine(void)
{
	int len = getMethod();
	size_t next = _read_buffer->find_first_of(' ', len + 1);
	if (next == std::string::npos && next != len + 1)
		throw HttpError(400);
	_request_target = _read_buffer->substr(len + 1, next - (len + 1));
	next = getVersion(next + 1);
	if (!isLineEnd(next))
		throw HttpError(400);
	_header_state = HEADER_FIELDS;
}

size_t HttpProtocol::getMethod(void)
{
	size_t pos = _read_buffer->find_first_of(' ');
	if (pos == std::string::npos)
		throw HttpError(400);
	std::string method = _read_buffer->substr(0, pos);
	if (method == "GET")
		_method = GET;
	else if (method == "HEAD")
		_method = HEAD;
	else if (method == "PUT")
		_method = PUT;
	else if (method == "DELETE")
		_method = DELETE;
	else if (method == "POST")
		_method = POST;
	else if (method == "CONNECT" || method == "OPTIONS" || method == "TRACE" || method == "PATCH")
		throw HttpError(501);
	else
		throw HttpError(400);
	return pos;
}

size_t HttpProtocol::getVersion(size_t i)
{
	if (_read_buffer->substr(i, 5) != "HTTP/")
		throw HttpError(400);

	i += 5;
	_major_version = (*_read_buffer)[i] - '0';
	if (_major_version < 0 || _major_version > 9)
		throw HttpError(400);

	if ((*_read_buffer)[i + 1] != '.')
		throw HttpError(400);

	_minor_version = (*_read_buffer)[i + 2] - '0';
	if (_minor_version < 0 || _minor_version > 9)
		throw HttpError(400);

	return i + 3;
}

//[[#DQUOTE]] ( ) , / : ; < = > ? @ \[ \\ ]{ }
void HttpProtocol::parseFieldLine(void)
{
	std::pair<std::string, std::string> fv_pair;
	int len = getLineLength(*_read_buffer);
	if (len == 2)
	{
		_framing_state = BODY;
		return;
	}
	size_t field_name_len = _read_buffer->find_first_of(':');
	if (field_name_len == std::string::npos || field_name_len == 0)
		throw HttpError(400);
	// std::string field_name = _read_buffer.substr(0, field_name_len);
	size_t field_value_start = field_name_len + 1;
	fv_pair.first = _read_buffer->substr(0, field_name_len);
	fv_pair.second = _read_buffer->substr(field_value_start, len - 2 - field_value_start);
	validateFieldName(fv_pair.first);
	scrubFieldValue(fv_pair.second);
	_header_fields.insert(fv_pair);
}

bool HttpProtocol::isLineEnd(size_t i)
{
	if ((*_read_buffer)[i] == '\r' && (*_read_buffer)[i + 1] == '\n')
		return true;
	return false;
}

void HttpProtocol::defensiveParseRequestLine(void)
{
	getMethod();
	throw HttpError(414, "URI probably too long");
}

bool HttpProtocol::isVCHAR(char c)
{
	//%21 - 7E
	if ((c >= '!' && c <= '~'))
		return true;
	return false;
}

bool HttpProtocol::isOBS(char c)
{
	//%80 - FF
	if (c >= 128 && c <= 255)
		return true;
	return false;
}

bool HttpProtocol::isTchar(char c)
{
	std::string delimiters = "\"(),/:;<>=?@[\\]{}";
	if (isVCHAR(c) && delimiters.find_first_of(c) == std::string::npos)
		return true;
	return false;
}

void HttpProtocol::validateFieldName(const std::string &str)
{
	if (str.size() == 0)
		throw HttpError(400);
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isTchar(str[i]))
			throw HttpError(400);
	}
}

void HttpProtocol::scrubFieldValue(std::string &str)
{
	if (str.size() == 0)
		return;
	if (str[0] == ' ')
		str.erase(0, 1);

	if (str.size() == 0)
		return;
	if (str[str.size() - 1] == ' ')
		str.erase(str.size() - 1, 1);

	if (str.size() == 0)
		return;
	if (!isVCHAR(str[0]) || !isVCHAR(str[str.size() - 1]))
		throw new HttpError(400);

	for (size_t i = 1; i < str.size() - 1; i++)
	{
		if (!(isVCHAR(str[i]) || str[i] == ' ' || str[i] == '\t' || isOBS(str[i])))
			throw new HttpError(400);
	}
}