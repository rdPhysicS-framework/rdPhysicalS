#ifndef	__CONTAINER_H__
#define	__CONTAINER_H__

#include "..\..\GlobalDefs.h"
#include "..\..\Util\LogError.h"
#include "base\PackageBase.h"
#include <map>
#include <string>
#include <vector>

RDPS_BEGIN
	PKG_BEGIN

		class ContainerBuilder;
		
		/********************************************************************************************************************************************
		 *
		 * Classe que contem todos os pacotes de objetos que serao enviados para
		 * serem processados. possui um std::map<string, PackageBase*> (packages) para facilitar
		 * adicionar os elementos nos arrays pelo id, pois é um array de arrays. Alem de ser um
		 * array generico.
		 * exemplo:
		 * packages[id]->AddElements(element);
		 *
		 ********************************************************************************************************************************************/
		class Container
		{
			friend ContainerBuilder;
		private:
			std::map<std::string, PackageBase*> packages;

		private:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			* Construtor padrão
			*---------------------------------------------------------------------------------------------------------------------------------------*/
			Container();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar de criacao de um pacote no id indicado.
			 * Se já houver algo no local retorna uma excecao.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Container &CreatePackage(std::string id, 
									 PackageBase *package);


		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~Container();

			const PackageBase *GetPackage(std::string id);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para verificar se existe um elemento pelo id indicado
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			bool ElementExists(std::string id) const;

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona um elemento no id indicado
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			inline Container &AddElement(std::string id,  T &element);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona varios elementos no id indicado
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			inline Container &AddElements(std::string id, std::vector<T> &element);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que remove um elemento do array de objetos
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Container &RemoveElement(std::string id, const int element);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que remove todos os elementos de um pacote
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Container &DestroyElements(std::string id);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que remove todos os elementos de todos os pacotes
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Container &DestroyElements();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que atualiza os dados nos pacotes.
			 * Obs:
			 * Só é preciso dar este comando de no inicio do prodama, foram iniciados
			 * os arrayBuffers como nullptr, ou se houve alguma alteracao nos dados
			 * da cena.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Container &Update();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que da o comando de envio das dados
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Container &ToSend();
			/*só para teste*/
			Container &ApplyBuffer();
		};

		template<class T>
		inline Container &Container::AddElement(std::string id, T &element)
		{
			if (packages.find(id) == packages.end())
			{
				Logger::Log("Attribute no exists : " + id);
			}

			packages[id]->AddElement(&element);

			return (*this);
		}

		template<class T>
		inline Container &Container::AddElements(std::string id, std::vector<T> &elements)
		{
			if (packages.find(id) == packages.end())
			{
				Logger::Log("Attribute no exists : " + id);
			}

			packages[id]->AddElements(&elements);

			
			return (*this);
		}

	PKG_END
RDPS_END

#endif//__CONTAINER_H__

