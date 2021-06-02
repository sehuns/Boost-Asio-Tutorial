#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;


// ���� ��ǻ���� ��¥ �� �ð� ������ ��ȯ
string make_daytime_string() //Ŭ���̾�Ʈ�� �������� �� ������
{
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try { 
		// 80�� : http, 13�� : daytime
		// �⺻������ Boost Asio ���α׷��� �ϳ��� IO Service ��ü�� ����
		boost::asio::io_service io_service;
		// TCP ���������� 13�� ��Ʈ�� ���� �޴� ���� ���� ����
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
		// ��� Ŭ���̾�Ʈ�� ���� ���� �ݺ� ����
		while (1)
		{
			// ���� ��ä�� ������ ���� ��ٸ�
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			// ���� �Ϸ�Ǹ� �ش� Ŭ���̾�Ʈ�� ���� �޽��� ����
			string message = make_daytime_string();
			// Ŭ���̾�Ʈ���� ����
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
	return 0;
}



