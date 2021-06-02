#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main()
{
	try
	{
		// �⺻������ �ϳ��� IO service ��ü ����
		boost::asio::io_service io_service;
		// ������ �̸��� TCP ���������� �ٲٱ� ���� �Լ�
		tcp::resolver resolver(io_service);
		// �����δ� ���� ����, ���񽺴� daytime ��������
		tcp::resolver::query query("0.tcp.ngrok.io", "12790");
		// DNS�� ���� IP �� ��Ʈ��ȣ ������
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		// ���� ��ü �ʱ�ȭ �Ͽ� ���� ����
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		while (1) {
			//���� �� ���� ó�� ���� ����
			boost::array<char, 128> buf;
			boost::system::error_code error;
			// ���۸� �̿��� �����κ��� ������ �޾ƿ�
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);
			//���ۿ� ��� ������ ���
			cout.write(buf.data(), len);
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}