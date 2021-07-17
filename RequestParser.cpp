#include "RequestParser.hpp"

RequestParser::RequestParser(void) : _headers()
{
	_isOk = 0;
	_global_len = 0;
    _contentLength = 0;


        _is_startline_ok = false;
		_is_headers_ok = false;
		_is_host = false;
		_is_body = false;
		_is_chunked = false;
		_is_length = false;
		_is_multipart = false;
		_is_application = false;
		_is_textPlain = false;
	_is_post = false;
}

const std::string RequestParser::space = " ";
const std::string RequestParser::separator = "\r\n";
const std::string RequestParser::double_separator = "\r\n\r\n";


RequestParser::RequestParser(const RequestParser &copy)
{
	*this = copy;
}

RequestParser &RequestParser::operator=(const RequestParser &copy)
{
	_isOk = copy._isOk;
	_is_host = copy._is_host;
	_is_chunked = copy._is_chunked;
	_is_headers_ok = copy._is_headers_ok;
	_is_body = copy._is_body;
	_is_startline_ok = copy._is_startline_ok;
	_is_multipart = copy._is_multipart;
	_is_length = copy._is_length;
	_contentLength = copy._contentLength;
	_global_len = copy._global_len;
	_str = copy._str;

    buf = copy.buf;
	_bodybuffer = copy._bodybuffer;

	_metod = copy._metod;
	_path = copy._path;
	_protokol = copy._protokol;
	_headers = copy._headers;
	_body = copy._body;
	_fullRequest = copy._fullRequest;
	return *this;
}

int RequestParser::RequestWaiter(const char *str, int len)
{
	size_t pos = 0;
    size_t pos2 = 0;

	std::string startline;
	std::string headers;

	std::string tmp_header;
	std::string tmp_header_rigth;
	std::string multipartName;

	std::string new_str ((char*)str, len);	//  Приводим к стрингу
	buf.append(new_str);				//  Добавляем приходящую строку в буфер

	pos = buf.find(separator);
	//	Стартлайн
	if ( (pos != std::string::npos) && _is_startline_ok != true ) // если есть \r\n и не было стартлайна, то парсим и удаляем все что до него
	{
		startline = buf.substr(0, pos);
		buf.erase(buf.begin(), buf.begin() + startline.length() + separator.length());
		pos = startline.find(" ");		// Достали метод из заголовка
		_metod = startline.substr(0, pos);
		startline.erase(0, _metod.length() + space.length());
		pos = startline.find(" ");		// Достали путь из заголовка
		_path = startline.substr(0, pos);
		startline.erase(0, _path.length() + space.length());
		pos = startline.find(" ");		// Достали протокол из заголовка
		_protokol = startline.substr(0, pos);
		startline.erase();
		_is_startline_ok = true;
	}

		// Стартлайн спарсили, парсим хедеры
	if ((((pos = buf.find(double_separator)) != std::string::npos))) // если есть \r\n\r\n парсим и удаляем все что до него
	{
		if (_is_headers_ok != true) // если не было хедеров
		{
			headers = buf.substr(0, pos + separator.length());  // отрезаем хедеры

			buf.erase(0, pos + double_separator.length());

			while ((pos = headers.find(separator)) != std::string::npos) // Отрезаем по 1-му хедеру и кладем в мап
			{
				tmp_header = headers.substr(0, pos);
				size_t pos2 = 0;
				pos2 = tmp_header.find(" ");
				tmp_header_rigth = tmp_header.substr(0, pos2);
				tmp_header.erase(0, tmp_header_rigth.length() + space.length());
				_headers.insert(std::pair<std::string,std::string>(tmp_header_rigth, tmp_header));
				headers.erase(0, tmp_header.length() + tmp_header_rigth.length() + separator.length() + space.length());
			}
		}
		_is_headers_ok = true;
	}

	if (_is_headers_ok == true) // понимаем будет ли тело?
	{
		std::map<std::string,std::string>::iterator it = _headers.begin();
		for (it = _headers.begin(); it != _headers.end(); ++it)
		{
			if ((it->first.compare("Transfer-Encoding:") == 0) && (it->second.compare("chunked") == 0))
				_is_chunked = true;
			if ((it->first.compare("Content-Length:") == 0))
			{
				_contentLength = atoi(it->second.c_str());
				_is_length = true;
			}
			if ((it->first.compare("Host:") == 0))
				_is_host = true;
			if ((it->first.compare("Content-Type:") == 0) && ((pos = it->second.find("multipart/form-data;")) != std::string::npos))
            {
			    _is_multipart = true;
            }
			if ((it->first.compare("Content-Type:") == 0) && ((pos = it->second.find("application/x-www-form-urlencoded")) != std::string::npos))
            {
			    _is_application = true;
            }
			if ((it->first.compare("Content-Type:") == 0) && ((pos = it->second.find("text/plain")) != std::string::npos))
            {
			    _is_textPlain = true;
            }

		}
	}

	//  начинаем читать тело Chunked
	if  (_is_chunked == true)
		{
			while (_is_body != true)
			{
				std::string bodydigit;

				long int bodydigit_dec;
				char * pEnd;

				pos = buf.find(separator);		// Нашли цифру
				bodydigit = buf.substr(0, pos);
				bodydigit_dec = strtol(bodydigit.c_str(), &pEnd, 16);
				if (bodydigit_dec > 0)
				{
					buf.erase(buf.begin(), buf.begin() + bodydigit.length() + separator.length());
					_bodybuffer.append(buf.substr(0, bodydigit_dec)); // Положили в буфер
					buf.erase(buf.begin(), buf.begin() + bodydigit_dec + separator.length());
				}
				if (bodydigit_dec == 0)
				{
					_is_body = true;
					buf.erase(buf.begin(), buf.end());
				}
			}
		}

    //  начинаем читать тело Multipart
    if  (_is_multipart == true)
    {


        _bodybuffer.append(buf);
        _global_len = _global_len + len;


        if ( (_global_len >= _contentLength) && _global_len != 0 )
        {

            _isOk = 1;
            if ((pos = buf.find(double_separator)) != std::string::npos) // убираем хедеры из тела мультипарт запроса спереди
            {
                if ((pos2 = buf.find("filename")) != std::string::npos)
                {
                    fileName = buf.substr(pos2 + 10);
                    if ((pos2 = fileName.find("\"")) != std::string::npos)
                        fileName = fileName.substr(0, pos2);
                }
                buf.erase(0, pos + double_separator.length());
            }
            if ((pos2 = buf.find(separator)) != std::string::npos) // убираем хедеры сзади
            {
                buf.erase(pos2, separator.length());
                if ((pos = buf.find(separator)) != std::string::npos)
                    buf.erase(pos2, pos + separator.length());
            }
            _bodybuffer.erase();
            _bodybuffer.append(buf);

        }
    }
	else if  (((_is_multipart != true) && ((_is_length == true) || (_contentLength > 0)) && _is_textPlain != true && _is_application == true)
			|| ((_is_multipart != true) && ((_is_length == true) || (_contentLength > 0)) && _is_application != true && _is_textPlain == true))
	{
			_bodybuffer.append(buf);
			_global_len = _global_len + len;
			_isOk = 2;
	}


	if (_is_startline_ok == true && _is_headers_ok == true)  //  проверяем стартлайн, мапу с хедерами и выставляем флаг is_ok
	{
		if (((_is_chunked == true) || (_is_length == true)) && (_is_body == true)) // если есть чанк или лен и боди собралось
					_isOk = 1;
		if ( (_is_host == true) && (_is_chunked == false) && (_is_length == false) ) // если есть тока хост
					_isOk = 1;
		else if (_isOk == 2)
			_isOk = 1;
	}

	return (_isOk);

}


void RequestParser::PrintMap()
{
	std::cout << "map contains:\n";
		std::map<std::string,std::string>::iterator it = _headers.begin();
  		for (it = _headers.begin(); it != _headers.end(); ++it)
    	std::cout << it->first << " " << it->second << '\n';


}

std::string RequestParser::getMetod()
{
	return (_metod);
}

std::string RequestParser::getPath()
{
	return (_path);
}

std::string RequestParser::getProtokol()
{
	return (_protokol);
}

std::map<std::string,std::string> RequestParser::getHeaders()
{
	return (_headers);
}

std::string RequestParser::getBody()
{
	return (_bodybuffer);
}

std::string RequestParser::getFileName()
{
    return (fileName);
}


RequestParser::~RequestParser()
{ }