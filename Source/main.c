#include "nrf.h"



int main()
{

	NRF24L01_Init();

	while(1)
	{}

}

void SendData() {
    uint8_t data = 1;  // Số 1 cần gửi
    NRF24L01_FlushTx();  // Xóa bộ đệm TX trước khi gửi
    NRF24L01_WriteTxPayload(&data, 1);  // Ghi số 1 vào TX FIFO
    // Đặt chân CSN lên cao để bắt đầu truyền
    GPIOA->BSRR = (1 << NRF24L01_CSN_PIN);
    // Đợi một thời gian ngắn để dữ liệu được gửi đi
    for (volatile int i = 0; i < 1000; i++);
    // Hạ chân CSN xuống để kết thúc truyền
    GPIOA->BRR = (1 << NRF24L01_CSN_PIN);
}
void button_callback()
{
	SendData();
}
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) { // Kiểm tra nếu ngắt từ EXTI0
        // Xử lý ngắt ở đây
        button_callback();

        EXTI->PR |= EXTI_PR_PR0; // Xóa cờ ngắt
    }
}

void gpio_interrupt()
{
	// Kích hoạt clock cho GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	// Kích hoạt clock cho AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	// Cấu hình PB0 là input pull-up/pull-down
	GPIOB->CRL &= ~(GPIO_CRL_MODE0);   // MODE0 = 00 (input mode)
	GPIOB->CRL &= ~(GPIO_CRL_CNF0_0);  // CNF0 = 10 (input with pull-up/pull-down)
	GPIOB->CRL |= GPIO_CRL_CNF0_1;
	// Chọn PB0 cho EXTI line 0
	AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0); // Clear bits
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB; // Set bits for PB0
	// Cấu hình EXTI cho PB0 (EXTI0)
	EXTI->IMR |= EXTI_IMR_MR0;  // Cho phép ngắt từ EXTI0
	EXTI->FTSR |= EXTI_FTSR_TR0; // Kích hoạt ngắt trên cạnh xuống (Falling edge)
	// Nếu muốn ngắt trên cạnh lên (Rising edge), sử dụng EXTI->RTSR |= EXTI_RTSR_TR0;
	// Kích hoạt ngắt EXTI0 trong NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);
}
void pb1_init()
{
	// Kích hoạt clock cho GPIOB (nếu chưa kích hoạt)
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	// Cấu hình PB1 là output push-pull
	GPIOB->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1); // Xóa các bits MODE1 và CNF1
	GPIOB->CRL |= GPIO_CRL_MODE1_1; // MODE1 = 10 (Output mode, max speed 2 MHz)
	                                 // CNF1 = 00 (General purpose output push-pull
}
