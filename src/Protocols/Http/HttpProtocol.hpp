/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpProtocol.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:28:42 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 18:18:13 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IProtocol.hpp"
#include "map"
#include "list"

class HttpProtocol : public IProtocol
{
private:
	enum method
	{
		GET,
		HEAD,
		PUT,
		DELETE,
		POST,
	};

	enum protoState
	{
		WAITING,
		MESSAGE,
		OUTPUT_READY
	};

	enum framingState
	{
		HEADER,
		BODY,
		TRAILING,
	};

	enum headerState
	{
		REQUEST_LINE,
		HEADER_FIELDS,
	};

	HttpProtocol::protoState _proto_state;
	HttpProtocol::framingState _framing_state;
	HttpProtocol::headerState _header_state;
	std::string *_read_buffer;
	// internal state to reset
	HttpProtocol::method _method;
	std::string _request_target;
	std::map<std::string, std::string> _header_fields;
	std::vector<std::string> _trailing_fields;
	std::string *_content;
	int _content_lenght;
	int _processed_content_lenght;

	int _major_version;
	int _minor_version;
	
	int _response_code;
	std::string _response_message;

	bool _discard;
public:
	HttpProtocol();
	HttpProtocol(const HttpProtocol &other);
	~HttpProtocol(void);
	HttpProtocol &operator=(const HttpProtocol &other);

	processAction processInput(std::string &input);
	outputAction output(std::string **out_loc);

private:
	int getLineLength(std::string &input) const;
	void reset(void);
	void parseRequestLine(void);
	void defensiveParseRequestLine(void);
	size_t getMethod(void);
	size_t getVersion(size_t start);
	bool isLineEnd(size_t i);
	void parseFieldLine(void);
	void validateFieldName(const std::string& str);
	void scrubFieldValue(std::string &str);

	bool isVCHAR(char c);
	bool isOBS(char c);
	bool isTchar(char c);
	

	class HttpError : public std::exception
	{
		private:
			int _response_code;
			std::string _detail;
		public:
			HttpError(int responseCode, const std::string &detail) : _response_code(responseCode), _detail(detail) {};
			HttpError(int responseCode) : _response_code(responseCode), _detail("") {};
			int code(void) const throw()
			{
				return _response_code;
			}
			const std::string & detail(void) const throw() {
				return _detail;
			}
			virtual ~HttpError(void) throw() {}
	};
};