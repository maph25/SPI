/*
 * SPI.c
 *
 *	\author Andrea Perez ie698276@iteso.mx & Fernanda Muñoz ie701371@iteso.mx
 *  \date	02/OCT/2018
 */
#include "SPI.h"
#include "GPIO.h"
#include "Bits.h"

/*Enables the clock*/
static void SPI_enable_clk(spi_channel_t channel){
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
			if(SPI_ENABLE_FIFO == enableOrDisable){
				SPI0->MCR &= ~SPI_MCR_DIS_TXF_MASK; /*Disable*/
			}
			else{
				SPI0->MCR |= SPI_MCR_DIS_TXF_MASK; /*Enable*/
			}
			break;
		case SPI_1:
			if(SPI_ENABLE_FIFO == enableOrDisable){
				SPI1->MCR &= ~SPI_MCR_DIS_TXF_MASK; /*Disable*/
			}
			else{
				SPI1->MCR |= SPI_MCR_DIS_TXF_MASK; /*Enable*/
			}
			break;
		case SPI_2:
			if(SPI_ENABLE_FIFO == enableOrDisable){
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
	switch(channel){
		case SPI_0:
			if(SPI_HIGH_PHASE == cpha){
				SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			}
			else{

				  SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			}
		break;
		case SPI_1:
			if(SPI_HIGH_PHASE == cpha){

			  SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			}
			else{

			  SPI1->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			}
		break;
		case SPI_2:
			if(SPI_HIGH_PHASE == cpha){
			  SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			}
			else{
			  SPI2->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			}
		break;

	}
}

static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate){
	switch(channel){
		case SPI_0:
			SPI0->CTAR[0] |= baudRate;
		break;
		case SPI_1:
			SPI1->CTAR[0] |= baudRate;
		break;
		case SPI_2:
			SPI2->CTAR[0] |= baudRate;
		break;
		default:
		break;
	}
}

static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb){
	switch(channel){
			case SPI_0:
				if(SPI_MSB == msb){
					SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
				}
				else{

					  SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
				}
			break;
			case SPI_1:
				if(SPI_MSB == msb){

				  SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
				}
				else{

				  SPI1->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
				}
			break;
			case SPI_2:
				if(SPI_MSB == msb){
				  SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
				}
				else{
				  SPI2->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
				}
			break;

		}
}

void SPI_start_tranference(spi_channel_t channel){
	switch(channel){
		case SPI_0:

			SPI0->MCR &= ~SPI_MCR_HALT_MASK;

			break;
		case SPI_1:
			SPI1->MCR &= ~SPI_MCR_HALT_MASK;
			break;
		case SPI_2:
			SPI2->MCR &= ~SPI_MCR_HALT_MASK;

			break;
		default:
			break;
	}
}

void SPI_stop_tranference(spi_channel_t channel){
	switch(channel){
		case SPI_0:
			SPI0->SR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->SR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_2:
			SPI2->SR |= SPI_MCR_HALT_MASK;
			break;
		default:
			break;
	}

}

/*A read access of PUSHR returns the topmost TX FIFO entry.*/
void SPI_send_one_byte(spi_channel_t channel, uint8_t Data){
	switch(channel)
		{
			case SPI_0 :
				SPI0->PUSHR = (Data);
				while(0 == (SPI0->SR & SPI_SR_TCF_MASK));
				SPI0->SR |= SPI_SR_TCF_MASK;
				break;

			case SPI_1 :
				SPI1->PUSHR = (Data);
				while(0 == (SPI1->SR & SPI_SR_TCF_MASK));
				SPI1->SR |= SPI_SR_TCF_MASK;
				break;

			case SPI_2 :
				SPI2->PUSHR = (Data);
				while(0 == (SPI2->SR & SPI_SR_TCF_MASK));
				SPI2->SR |= SPI_SR_TCF_MASK;
			  break;

			default:
				  return;
		}
}

void SPI_init(const spi_config_t* spi_config)
{
 gpio_pin_control_register_t enable_bit = GPIO_MUX1;
 SPI_clk(spi_config->spi_channel);
 GPIO_clock_gating(spi_config->spi_gpio_port.gpio_port_name);
 GPIO_pin_control_register(spi_config->spi_gpio_port.gpio_port_name, spi_config->spi_gpio_port.spi_clk, &(spi_config->pin_config));
 GPIO_pin_control_register(spi_config->spi_gpio_port.gpio_port_name ,spi_config->spi_gpio_port.spi_sout ,&(spi_config->pin_config));
 SPI_set_master(spi_config->spi_channel,spi_config->spi_master);
 SPI_fifo(spi_config->spi_channel, spi_config->spi_enable_fifo);
 SPI_enable(spi_config->spi_channel);
 SPI_clock_polarity(spi_config->spi_channel, spi_config->spi_polarity);
 SPI_frame_size(spi_config->spi_channel,spi_config->spi_frame_size);
 SPI_clock_phase(spi_config->spi_channel, spi_config->spi_phase);
 SPI_baud_rate(spi_config->spi_channel, spi_config->spi_baudrate);
 SPI_msb_first(spi_config->spi_channel, spi_config->spi_lsb_or_msb);

 GPIO_pin_control_register(GPIO_D, bit_4, &enable_bit);
 GPIO_set_pin(GPIO_D, bit_4);
 GPIO_data_direction_pin(GPIO_D, GPIO_OUTPUT, bit_4);
}
