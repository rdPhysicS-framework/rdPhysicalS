#ifndef	__PACKAGE_H__
#define	__PACKAGE_H__

#include "base\PackageBase.h"
#include "..\ArrayBuffer.h"

RDPS_BEGIN
	PKG_BEGIN
		/********************************************************************************************************************************************
		 *
		 * Classe responsavel por armazenar os objetos que serão enviados para a aplicação OpenCL.
		 * Possui uma lista de objetos genericos, e um ArrayBuffer para lincar com a Aplicação
		 * OpenCL. Herda de Package base para o polimorfismo.
		 * Obs:
		 *	   - O tipo T não pode ser ponteiro, pois a openCL nao suporta ponteiros de ponteiros.
		 *
		 ********************************************************************************************************************************************/
		template<class T>
		class Package : public PackageBase
		{
		private:
			std::vector<T> elements;
			ArrayBuffer<T> *buffer;

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * recebe como parametro o tipo de acao para o ArrayBuffer (leitura ou escrita)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Package(const ActionFile typeAction = RETURN_DATA_WRITING);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * recebe como parametro uma array de elementos e o tipo de acao para o ArrayBuffer (leitura ou escrita)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Package(const std::vector<T> &_elements, 
					const ActionFile typeAction = RETURN_DATA_WRITING);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~Package();

			Package<T> &operator=(const Package<T> &other);

			virtual size_t Size() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para adicionar um elemento no array
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual Package<T> &AddElement(void *_element);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para adicionar varios elementos no array
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual Package<T> &AddElements(void *_elements);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que remove um elemento do array de objetos
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual Package<T> &RemoveElement(const int id);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que limpa o array
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual Package<T> &DestroyElements();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para atualizar os dados do ArrayBuffer
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual Package<T> &Update();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que da o comando para envio dos dados 
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual Package<T> &ToSend();

			virtual Package<T> &ApplyBuffer();
		};

		template<class T>
		inline Package<T>::Package(const ActionFile typeAction) :
						   buffer(new ArrayBuffer<T>(typeAction))
		{}

		template<class T>
		inline Package<T>::Package(const std::vector<T> &_elements,
								   const ActionFile typeAction) :
						   elements(_elements),
						   buffer(new ArrayBuffer<T>(
										const_cast<T*>(_elements.data()),
										_elements.size(),
										typeAction                        ))
		{}

		template<class T>
		inline Package<T>::~Package()
		{
			delete buffer;
			elements.clear();
		}

		template<class T>
		inline Package<T> &Package<T>::operator=(const Package<T> &other)
		{
			elements = other.elements;
			buffer = other.buffer;
			return (*this);
		}

		template<class T>
		inline size_t Package<T>::Size() const
		{
			return elements.size();
		}

		template<class T>
		inline Package<T> &Package<T>::AddElement(void *_element)
		{
			elements.push_back(*static_cast<T*>(_element));
			return (*this);
		}

		template<class T>
		inline Package<T> &Package<T>::AddElements(void *_elements)
		{
			elements = *static_cast<std::vector<T>*>(_elements);
			return (*this);
		}

		template<class T>
		inline Package<T> &Package<T>::RemoveElement(const int id)
		{
			elements.erase(elements.begin() + id);
			return (*this);
		}

		template<class T>
		inline Package<T> &Package<T>::DestroyElements()
		{
			elements.clear();
			return (*this);
		}

		template<class T>
		inline Package<T> &Package<T>::Update()
		{
			buffer->UpdateData(const_cast<T*>(
								   elements.data()), 
							   elements.size()      );
			return (*this);
		}

		template<class T>
		inline Package<T> &Package<T>::ToSend()
		{
			buffer->Binding();
			return (*this);
		}

		template<class T>
		inline Package<T> &Package<T>::ApplyBuffer()
		{
			buffer->Apply();
			return (*this);
		}

	PKG_END
RDPS_END
#endif//__PACKAGE_H__

