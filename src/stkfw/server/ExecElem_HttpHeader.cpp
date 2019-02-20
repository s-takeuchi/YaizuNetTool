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
	size_t Result;
	LowDbAccess::GetInstance()->GetHttpHeaderInfo(ElementId, &intput_bin, tmp_http_header);
	wcstombs_s(&Result, presented_http_header, 1024,  tmp_http_header, 1024);
	if (intput_bin & 0x01) {
		http_header_del = true;
	}
	if (intput_bin & 0x02) {
		http_header_add = true;
	}

	char* data = (char*)GetData();
	char* data_ptr = data;
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
				char date_work[128] = "";
				int date_work_len = 0;
				/***** Make time string begin *****/
				struct tm GmtTime;
				__int64 Ltime;
				_time64(&Ltime);
				_gmtime64_s(&GmtTime, &Ltime);
				char MonStr[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
				char WdayStr[7][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
				sprintf_s(date_work, 128, "Date: %s, %02d %s %d %02d:%02d:%02d GMT\r\n",
					WdayStr[GmtTime.tm_wday],
					GmtTime.tm_mday,
					MonStr[GmtTime.tm_mon],
					GmtTime.tm_year + 1900,
					GmtTime.tm_hour,
					GmtTime.tm_min,
					GmtTime.tm_sec);
				/***** Make time string end *****/
				date_work_len = strlen(date_work);
				if (new_data_ptr + date_work_len - new_data < 10000000 - 1) {
					strncpy_s(new_data_ptr, 10000000 - (new_data_ptr - new_data), date_work, date_work_len);
					new_data_ptr += date_work_len;
				}
			} else if (strncmp(presented_http_header_ptr, "Content-Length: <automatically replaced>\r\n", 42) == 0) {
				char cont_len_work[128] = "";
				int cont_len_work_len = 0;
				sprintf_s(cont_len_work, 128, "Content-Length: %d\r\n", data_end_ptr - data_ptr);
				cont_len_work_len = strlen(cont_len_work);
				if (new_data_ptr + cont_len_work_len - new_data < 10000000 - 1) {
					strncpy_s(new_data_ptr, 10000000 - (new_data_ptr - new_data), cont_len_work, cont_len_work_len);
					new_data_ptr += cont_len_work_len;
				}
			} else {
				for (char* i = presented_http_header_ptr; i < tmp_ptr; i++) {
					if (new_data_ptr - new_data + 1 < 10000000 - 1) {
						*new_data_ptr = *i;
						*new_data_ptr++;
					}
				}
			}

			presented_http_header_ptr = tmp_ptr;
			tmp_ptr = strstr(presented_http_header_ptr, "\r\n");
		}
		if (new_data_ptr - new_data + 2 < 10000000 - 1) {
			strncpy_s(new_data_ptr, 10000000 - (new_data_ptr - new_data), "\r\n", 2);
			new_data_ptr += 2;
		}
	}
	for (char* i = (char*)data_ptr; i < data_end_ptr; i++) {
		if (new_data_ptr - new_data + 1 < 10000000) {
			*new_data_ptr = *i;
			new_data_ptr++;
		}
	}
	delete data;
	SetData(new_data);
	SetDataLength(new_data_ptr - new_data);
	return 0;
}
