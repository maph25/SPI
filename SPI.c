/*
 * SPI.c
 *
 *	\author Andrea Perez ie698276@iteso.mx & Fernanda Muñoz ie701371@iteso.mx
 *  \date	02/OCT/2018
 */
#include "SPI.h"
#include "GPIO.h"

/*Enables the clock*/
static void SPI_enable_clock(spi_channel_t channel){
	switch(channel){
			case SPI_0:
				SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);
				break;
			case SPI_1:
				SPI1->MCR &= ~(SPI_MCR_MDIS_MASK);
				break;
			case SPI_2:
				SPI2->MCR &= ~(SPI_MCR_MDIS_MASK);
				break;
			default:
				break;
		}
}

static void SPI_clk(spi_channel_t channel){
	switch(channel){
	case SPI_0:
		SIM->SCGC6 |= SPI0_CLOCK_GATING;
		break;
	case SPI_1:
		SIM->SCGC6 |= SPI1_CLOCK_GATING;
		break;
	case SPI_2:
		SIM->SCGC3 |= SPI2_CLOCK_GATING;
		break;
	default:
		return;
	}
}
/*Activates clock gating*/
/*static void SPI_clk(spi_channel_t channel){
	switch(channel){
		case SPI_0:
			SPI0->MCR = (SPI0_CLOCK_GATING) &~(SPI_MCR_CONT_SCKE_MASK);
			break;
		case SPI_1:
			SPI1->MCR = (SPI1_CLOCK_GATING) &~(SPI_MCR_CONT_SCKE_MASK);
			break;
		case SPI_2:
			SPI2->MCR = (SPI2_CLOCK_GATING) &~(SPI_MCR_CONT_SCKE_MASK);
			break;
		default:
			break;
	}
}*/

static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave){
	switch(channel){
		case SPI_0:
			if(SPI_MASTER == masterOrSlave){
				SPI0->MCR |= (SPI_MCR_MSTR_MASK); /*MASTER ENABLE*/
			}
			else{
				SPI0->MCR &= ~(SPI_MCR_MSTR_MASK); /*SLAVE ENABLE*/
			}
			break;
		case SPI_1:
			if(SPI_MASTER == masterOrSlave){
				SPI1->MCR |= (SPI_MCR_MSTR_MASK); /*MASTER ENABLE*/
			}
			else{
				SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);/*SLAVE ENABLE*/
			}
			break;
		case SPI_2:
			if(SPI_MASTER == masterOrSlave){
				SPI2->MCR |= (SPI_MCR_MSTR_MASK);/*MASTER ENABLE*/
			}
			else{
				SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);/*SLAVE ENABLE*/
			}
			break;
		default:
			break;
	}
}

static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable){
	switch(channel){
		case SPI_0:
			if(SPI_DISABLE_FIFO == enableOrDisable){
				SPI0->MCR &= ~SPI_MCR_DIS_TXF_MASK; /*Disable*/
			}
			else{
				SPI0->MCR |= SPI_MCR_DIS_TXF_MASK; /*Enable*/
			}
			break;
		case SPI_1:
			if(SPI_DISABLE_FIFO == enableOrDisable){
				SPI1->MCR &= ~SPI_MCR_DIS_TXF_MASK; /*Disable*/
			}
			else{
				SPI1->MCR |= SPI_MCR_DIS_TXF_MASK; /*Enable*/
			}
			break;
		case SPI_2:
			if(SPI_DISABLE_FIFO == enableOrDisable){
				SPI2->MCR &= ~SPI_MCR_DIS_TXF_MASK; /*Disable*/
			}
			else{
				SPI2->MCR |= SPI_MCR_DIS_TXF_MASK; /*Enable*/
			}
			break;
		default:
			break;
	}
}

static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol){
	switch(channel){
		case SPI_0:
			if(SPI_HIGH_POLARITY == cpol){
				  SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			}
			else{

				  SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		case SPI_1:
			if(SPI_HIGH_POLARITY == cpol){

				  SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			}
			else{

				  SPI1->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		case SPI_2:
			if(SPI_HIGH_POLARITY == cpol){
				  SPI2->CTAR[0]|= SPI_CTAR_CPOL_MASK;
			}
			else{

				  SPI2->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
			}
			break;
		}
}

static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize){
	switch(channel){
			case SPI_0:
				SPI0->CTAR[0] |= frameSize;
				break;
			case SPI_1:
				SPI1->CTAR[0] |= frameSize;
				break;
			case SPI_2:
				SPI2->CTAR[0] |= frameSize;
				break;
			default:
				break;
	}
}

static void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha){

}

static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate){

}

static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb){

}

void SPI_start_tranference(spi_channel_t channel){

}

void SPI_stop_tranference(spi_channel_t channel){

}

void SPI_send_one_byte(uint8_t Data){

}

