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
			 * 1- contem os números dos itens global em cada dimenção, (o total de itens divididos entre as dimenções) 
			 *
			 * --- Detalhe Importante ---
			 * Itens Globais são os itens que serão processados em paralelo no DISPOSITIVO.
			 * Não são o número de grupos de trabalhos.
			 *
			 * 2- contem os números dos itens globais em cada grupo de trabalho, 
			 *    também em cada dimenção.
			 * 3- contem os números de quantos em quantos itens será pulado em cada dimenção.
			 *
			 * O numero de dimenções é 3 no maximo e no minimo 1, todos precisão ter o mesmo número de dimenções.
			 * Funciona como uma matriz. 
			 * É necessário setar pelo menos o gItemSize com pelo menos 
			 * uma dimenção para que possa ser executado o EnqueueNDRangeKernel.
			 * Exemplo:
			 * ItensWorkGroupComponent itens = ItensWorkGroupComponent({16}, {}, {});
			 * 
			 * A quantidade que será passada nas chaves que define as dimenções.
			 * 
			 * ---IMPORTANTE---
			 * Dimeções erradas pode não funcionar corretamente a aplicação. O mesmo pros valores.
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
			 * Retorna o número de dimenções do grupo de trabalho
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
