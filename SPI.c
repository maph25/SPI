/*
 * SPI.c
 *
 *  Created on: 03/10/2018
 *      Author: Fer Muñoz, Andrea Perez
 */
#include "SPI.h"


static void SPI_enable_clk(spi_channel_t channel){
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_MDIS_MASK;
		break;
		case SPI_1:
			SPI1->MCR &= ~SPI_MCR_MDIS_MASK;
		break;
		case SPI_2:
			SPI2->MCR &= ~SPI_MCR_MDIS_MASK;
		break;
	}

}

static void SPI_clk(spi_channel_t channel){
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
	}
}

static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave){

}

static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable){

}

static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol){

}

static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize){

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

void SPI_init(const spi_config_t*){

}
