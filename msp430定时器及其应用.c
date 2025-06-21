#include <msp430.h>
unsigned char bSayac=0; // Kesme sayaç değişkeni
void main(void) {
WDTCTL = WDTPW | WDTHOLD; // Watchdog timeri durdur.
BCSCTL1 = CALBC1_1MHZ; // Dahili osilatörü 1MHz'e ayarla.
DCOCTL = CALDCO_1MHZ; // Dahili osilatörü 1MHz'e ayarla.
P1DIR |= BIT0; // Port1.0 çıkış.
CCTL0 = CCIE; // CCR0 kesmesini aç
CCR0 = 50000; // CCR0 50 ms ayarla.
TACTL = TASSEL_2 + MC_2; // Zamanlayıcı ayarları.
_BIS_SR(LPM0_bits + GIE); // LPM0 moduna gir kesmeleri aç.
}
#pragma vector=TIMER0_A0_VECTOR // Timer0_A0 kesme vektörü
__interrupt void Timer_A (void)
{
if(++bSayac==10){ // Sayaç 10 olmuş mu?
P1OUT ^= BIT0; // Port1.0'ı tersle.
bSayac = 0; } // Sayacı sıfırla.
CCR0 += 50000; // CCR0'ı tekrar kur.
