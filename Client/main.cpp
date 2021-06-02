#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main()
{
	try
	{
		// 기본적으로 하나의 IO service 객체 가짐
		boost::asio::io_service io_service;
		// 도메인 이름을 TCP 종단점으로 바꾸기 위한 함수
		tcp::resolver resolver(io_service);
		// 서버로는 로컬 서버, 서비스는 daytime 프로토콜
		tcp::resolver::query query("0.tcp.ngrok.io", "12790");
		// DNS를 거쳐 IP 및 포트번호 가져옴
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		// 소켓 개체 초기화 하여 서버 연결
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		while (1) {
			//버퍼 및 오류 처리 변수 선언
			boost::array<char, 128> buf;
			boost::system::error_code error;
			// 버퍼를 이용해 서버로부터 데이터 받아옴
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);
			//버퍼에 담긴 데이터 출력
			cout.write(buf.data(), len);
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}