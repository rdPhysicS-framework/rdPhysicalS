#ifndef __ITENS_WORK_GROUP_COMPONENETE_H__
#define __ITENS_WORK_GROUP_COMPONENETE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		/***************************************************************************************************************
		 *
		 * Classe auxiliar para definir os itens de trabalhos para que os 
		 * dados sejam processados em paralelo
		 *
		 ***************************************************************************************************************/
		class ItensWorkGroupComponent
		{
		private:
			std::vector<size_t> globalItemSize;
			std::vector<size_t> localWorkItemSize;
			std::vector<size_t> offSet;

		public:
			/*----------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Recebe como parametro 3 initializer_list<size_t>. 
			 * 1- contem os n�meros dos itens global em cada dimen��o, (o total de itens divididos entre as dimen��es) 
			 *
			 * --- Detalhe Importante ---
			 * Itens Globais s�o os itens que ser�o processados em paralelo no DISPOSITIVO.
			 * N�o s�o o n�mero de grupos de trabalhos.
			 *
			 * 2- contem os n�meros dos itens globais em cada grupo de trabalho, 
			 *    tamb�m em cada dimen��o.
			 * 3- contem os n�meros de quantos em quantos itens ser� pulado em cada dimen��o.
			 *
			 * O numero de dimen��es � 3 no maximo e no minimo 1, todos precis�o ter o mesmo n�mero de dimen��es.
			 * Funciona como uma matriz. 
			 * � necess�rio setar pelo menos o gItemSize com pelo menos 
			 * uma dimen��o para que possa ser executado o EnqueueNDRangeKernel.
			 * Exemplo:
			 * ItensWorkGroupComponent itens = ItensWorkGroupComponent({16}, {}, {});
			 * 
			 * A quantidade que ser� passada nas chaves que define as dimen��es.
			 * 
			 * ---IMPORTANTE---
			 * Dime��es erradas pode n�o funcionar corretamente a aplica��o. O mesmo pros valores.
			 *----------------------------------------------------------------------------------------------------------*/
			ItensWorkGroupComponent(const std::initializer_list<size_t> gItemSize,
								    const std::initializer_list<size_t> lwItemSize = {},
									const std::initializer_list<size_t> _offSet = {});

			/*----------------------------------------------------------------------------------------------------------
			 * Destrutor
			 *----------------------------------------------------------------------------------------------------------*/
			~ItensWorkGroupComponent();

			/*----------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Retorna o n�mero de dimen��es do grupo de trabalho
			 *----------------------------------------------------------------------------------------------------------*/
			const cl_uint  GetDimensions()  const;
			/*----------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Retorna um ponteiro contendo os itens globais 
			 *----------------------------------------------------------------------------------------------------------*/
			inline const size_t *GetGlobalItens() const { return globalItemSize.data();    }
			/*----------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Retorna um ponteiro contendo os itens locais em um grupo
			 *---------------------------------------------------------------------------------------------------------*/
			inline const size_t *GetLocalItens()  const { return localWorkItemSize.data(); }
			/*----------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Retorna um ponteiro contendo o offset
			 *---------------------------------------------------------------------------------------------------------*/
			inline const size_t *GetOffSet()	  const { return offSet.data();            }
		};
	CL_END
RDPS_END

#endif //__ITENS_WORK_GROUP_COMPONENETE_H__
