#ifndef	__ARRAY_BUFFER_H__
#define	__ARRAY_BUFFER_H__

#include <iostream>
#include "../GlobalDefs.h"
#include "../World.h"

RDPS_BEGIN
	PKG_BEGIN
		/********************************************************************************************************************************************
		 * 
		 * Classe responsavel em armazenar os dados que serão enviados para
		 * o dispositivo openCL. 
		 * Nela Contem:
		 * -> id: O id do objeto na função kernel para escrita, leitura;
		 * -> element: O elemento que será enviado para o dispositivo;
		 * -> butes : Quantos bytes ele possui para leitura ou escrita no dispositivo;
		 * -> typeAction: E qual será a ação no dispositivo retorno para leitura (RETUR_DATA_READING),
		 *    retorno para escrita(RETUR_DATA_WRITING), retorno para copia de dados
		 *    na função kernel (RETURN_DATA_COPY);
		 *
		 ********************************************************************************************************************************************/
		template<class T>
		class ArrayBuffer 
		{
		private:
			int id;
			T *element;
			size_t bytes;
			ActionFile typeAction;

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * recebe um parametro que diz qual será a sua acao de leitura ou escrita de dados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ArrayBuffer(const ActionFile _typeAction = NONE);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * recebe um ponteiro para os dados que serão enviados,
			 * a quantidade de elementos para o calculo dos bytes,
			 * e qual será a sua acao de leitura ou escrita de dados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ArrayBuffer(T *data, 
						const size_t size, 
						const ActionFile _typeAction = NONE);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ArrayBuffer(const ArrayBuffer<T> &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrão
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~ArrayBuffer();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Retorna o id
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline int GetId() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Retorna os bytes
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline size_t GetBytes() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Retorna o ponteiro com os elementos
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline T *GetElement() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Retorna o tipo da ação
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline ActionFile GetTypeAction() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Retorna adiciona o id
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline void SetId(const int _id);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função de sobrecarga de operador para cópia de dados de outro arrayBuffer
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline ArrayBuffer<T> &operator=(const ArrayBuffer<T> &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que atualiza os dados no aplicativo (se preciso).
			 * Caso ocorra alguma atualizado com os dados referentes, necessita resetar o
			 * objeto de memória no aplicativo, e enviar os dados e o tamanho em bytes novamente
			 * para o aplicativo recriando outro objeto de memória no mesmo id. Assim atualizando
			 * na GPU.
			 * Obs: A instancia do MemObjectComponent não é destruido e sim o membro (cl_mem)
			 *		dentro da classe. Assim ocorre apenas um set na aplicação. Mas, se id referente
			 *		nao existir na lista entao sera instanciado um MemObjectComponent.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline ArrayBuffer<T> &UpdateData(T *data, const size_t size);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que da o comando para setar o attributo pelo id e processar os dados
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline ArrayBuffer<T> Binding() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que da o comando para aplicar a acao de leitura ou escrita no buffer
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline ArrayBuffer<T> Apply();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			* Função auxiliar que adiciona o elemento de processamento para nullptr.
			*---------------------------------------------------------------------------------------------------------------------------------------*/
			inline ArrayBuffer<T> DestroyElement();
		};

		template<class T>
		inline ArrayBuffer<T>::ArrayBuffer(const ActionFile _typeAction) :
							   id(ARRAY_WITHOUT_INDEX),
							   element(nullptr),
							   bytes(0),
							   typeAction(_typeAction)
		{
			id = WORLD_GET_APP->GetBuffer();
		}

		template<class T>
		inline ArrayBuffer<T>::ArrayBuffer(T *data, 
										   const size_t size, 
										   const ActionFile _typeAction) :
							   id(ARRAY_WITHOUT_INDEX),
							   element(data), 
							   bytes(sizeof(T) * size),
							   typeAction(_typeAction)
		{
			/*como vai ser*/
			id = WORLD_GET_APP->CreateBuffer(id, typeAction, bytes);
		}

		template<class T>
		inline ArrayBuffer<T>::ArrayBuffer(const ArrayBuffer<T> &other) :
							   id(other.id),
							   element(other.element),
							   bytes(other.bytes),
							   typeAction(other.typeAction)
		{}

		template<class T>
		inline ArrayBuffer<T>::~ArrayBuffer()
		{}

		template<class T>
		inline int ArrayBuffer<T>::GetId() const
		{
			return id;
		}

		template<class T>
		inline size_t ArrayBuffer<T>::GetBytes() const
		{
			return bytes;
		}

		template<class T>
		inline T *ArrayBuffer<T>::GetElement() const
		{
			return element;
		}

		template<class T>
		inline ActionFile ArrayBuffer<T>::GetTypeAction() const
		{
			return typeAction;
		}

		template<class T>
		inline void ArrayBuffer<T>::SetId(const int _id)
		{
			id = _id;
		}

		template<class T>
		inline ArrayBuffer<T> &ArrayBuffer<T>::operator=(const ArrayBuffer<T> &other)
		{
			id = other.id;
			bytes = other.bytes;
			typeAction = other.typeAction;
			element = other.element;
			/*int size = other.bytes / sizeof(T);
			memcpy(element, (void*)other.element, size);*/
			return (*this);
		}

		template<class T>
		inline ArrayBuffer<T> &ArrayBuffer<T>::UpdateData(T *data, const size_t size)
		{
			element = data;
			bytes = sizeof(T) * size;

			if (WORLD_GET_APP->GetBuffer(id) == BUSY_LOCATION)
			{
				WORLD_GET_APP->DestroyBuffer(id);
			}

			id = WORLD_GET_APP->CreateBuffer(id, typeAction, bytes);

			return (*this);
		}

		template<class T>
		inline ArrayBuffer<T> ArrayBuffer<T>::Binding() const
		{
			WORLD_GET_APP->ApplyArgument(id);
			return (*this);
		}

		template<class T>
		inline ArrayBuffer<T> ArrayBuffer<T>::Apply()
		{
			WORLD_GET_APP->ApplyBuffer(id, typeAction, bytes, element);
			return (*this);
		}

		template<class T>
		inline ArrayBuffer<T> ArrayBuffer<T>::DestroyElement()
		{
			element = nullptr;
			bytes = 0;
			return (*this);
		}


	PKG_END
RDPS_END

#endif//__ARRAY_BUFFER_H__