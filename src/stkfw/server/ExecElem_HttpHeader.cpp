#include <cwchar>
#include <cstring>
#include "ExecElem_HttpHeader.h"
#include "LowDbAccess.h"
#include <windows.h>

ExecElem_HttpHeader::ExecElem_HttpHeader(int Id) : ExecElem(Id)
{
}

// Destructor
ExecElem_HttpHeader::~ExecElem_HttpHeader()
{
}

int ExecElem_HttpHeader::Execute()
{
	wchar_t tmp_http_header[1024];

	char presented_http_header[1024];
	char* presented_http_header_ptr = presented_http_header;

	int intput_bin = 0;
	bool http_header_del = false;
	bool http_header_add = false;
	LowDbAccess::GetInstance()->GetHttpHeaderInfo(ElementId, &intput_bin, tmp_http_header);
	wcstombs(presented_http_header, tmp_http_header, 1024 - 1);
	if (intput_bin & 0x01) {
		http_header_del = true;
	}
	if (intput_bin & 0x02) {
		http_header_add = true;
	}

	char* data = (char*)GetData();
	char* data_ptr = NULL;
	char* data_end_ptr = (char*)data + GetDataLength();

	char* new_data = new char[10000000];
	char* new_data_ptr = new_data;

	if (http_header_del) {
		if (strncmp(data, "GET", 3) == 0 ||
			strncmp(data, "HEAD", 4) == 0 ||
			strncmp(data, "POST", 4) == 0 ||
			strncmp(data, "PUT", 3) == 0 ||
			strncmp(data, "DELETE", 6) == 0 ||
			strncmp(data, "CONNECT", 7) == 0 ||
			strncmp(data, "OPTIONS", 7) == 0 ||
			strncmp(data, "TRACE", 5) == 0 ||
			strncmp(data, "PATCH", 5) == 0 ||
			strncmp(data, "HTTP/", 5) == 0) {
			for (data_ptr = data; data_ptr < data_end_ptr && strncmp(data_ptr, "\r\n\r\n", 4); data_ptr++);
			if (data_ptr == data_end_ptr) {
				for (data_ptr = data; data_ptr < data_end_ptr && strncmp(data_ptr, "\n\n", 2); data_ptr++);
				if (data_ptr == data_end_ptr) {
					data_ptr = data;
				} else {
					data_ptr += 2;
				}
			} else {
				data_ptr += 4;
			}
		}
	}
	if (http_header_add) {
		char* tmp_ptr = strstr(presented_http_header_ptr, "\r\n");
		while (tmp_ptr) {
			tmp_ptr += 2;
			if (strncmp(presented_http_header_ptr, "Date: <automatically replaced>\r\n", 32) == 0) {
				strncpy(new_data_ptr, "Date: 111\r\n", 11);
				new_data_ptr += 11;
			} else if (strncmp(presented_http_header_ptr, "Content-Length: <automatically replaced>\r\n", 42) == 0) {
				strncpy(new_data_ptr, "Content-Length: 111\r\n", 21);
				new_data_ptr += 21;
			} else {
				for (char* i = presented_http_header_ptr; i < tmp_ptr; i++) {
					*new_data_ptr = *i;
					*new_data_ptr++;
				}
			}

			presented_http_header_ptr = tmp_ptr;
			tmp_ptr = strstr(presented_http_header_ptr, "\r\n");
		}
		strncpy(new_data_ptr, "\r\n", 2);
		new_data_ptr += 2;
	}
	for (char* i = (char*)data_ptr; i < data_end_ptr; i++) {
		*new_data_ptr = *i;
		new_data_ptr++;
	}
	*new_data_ptr = '\0';
	delete data;
	SetData(new_data);
	SetDataLength(new_data_ptr - new_data + 1);
	return 0;
}
