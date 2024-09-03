# Taycam
NRF24L01_LowLevelInit():
Đây là hàm khởi tạo cấp thấp cho phần cứng.
Bật clock cho GPIOA và SPI1.
Cấu hình các chân GPIO cho SPI (SCK, MISO, MOSI).
Cấu hình các chân CE và CSN.
Cấu hình SPI1 với các tham số cần thiết.
NRF24L01_SendByte(uint8_t byte):
Hàm này gửi một byte qua SPI và đồng thời đọc một byte trả về.
Đợi cho đến khi buffer truyền sẵn sàng (TXE).
Ghi byte cần gửi vào DR (Data Register).
Đợi cho đến khi nhận được dữ liệu (RXNE).
Trả về byte đã nhận.
NRF24L01_Init():
Hàm khởi tạo chính cho module NRF24L01.
Gọi NRF24L01_LowLevelInit() để cấu hình phần cứng.
Thiết lập trạng thái ban đầu cho CE và CSN.
Cấu hình các thanh ghi của NRF24L01 với các giá trị mặc định.
NRF24L01_WriteReg(uint8_t reg, uint8_t value):
Ghi một giá trị vào một thanh ghi cụ thể của NRF24L01.
Kéo CSN xuống thấp để bắt đầu giao tiếp.
Gửi lệnh ghi thanh ghi kèm địa chỉ thanh ghi.
Gửi giá trị cần ghi.
Kéo CSN lên cao để kết thúc giao tiếp.
NRF24L01_ReadReg(uint8_t reg):
Đọc giá trị từ một thanh ghi cụ thể của NRF24L01.
Tương tự như WriteReg, nhưng sử dụng lệnh đọc và đọc giá trị trả về.
NRF24L01_WriteTxPayload(uint8_t *data, uint8_t length):
Ghi dữ liệu vào TX payload của NRF24L01.
Gửi lệnh W_TX_PAYLOAD.
Gửi từng byte dữ liệu.
NRF24L01_ReadRxPayload(uint8_t *data, uint8_t length):
Đọc dữ liệu từ RX payload của NRF24L01.
Gửi lệnh R_RX_PAYLOAD.
Đọc từng byte dữ liệu và lưu vào buffer.
NRF24L01_FlushTx() và NRF24L01_FlushRx():
Xóa FIFO TX hoặc RX bằng cách gửi lệnh tương ứng.
Các hàm này cung cấp các chức năng cơ bản để giao tiếp với module NRF24L01:

Khởi tạo và cấu hình module.
Đọc và ghi các thanh ghi cấu hình.
Gửi và nhận dữ liệu.
Xóa các buffer khi cần thiết.
Khi sử dụng thư viện này, người dùng sẽ chủ yếu tương tác với các hàm cấp cao như NRF24L01_Init(), NRF24L01_WriteTxPayload(), và NRF24L01_ReadRxPayload() để thiết lập và sử dụng module NRF24L01
