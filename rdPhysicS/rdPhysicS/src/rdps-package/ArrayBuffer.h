#ifndef	__ARRAY_BUFFER_H__
#define	__ARRAY_BUFFER_H__

#include <iostream>
#include "../GlobalDefs.h"

#define ARRAY_WITHOUT_INDEX -1

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
			 * recebe um ponteiro para os dados que serão enviados,
			 * e tambem a quantidade que será enviado para o calculo dos bytes.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ArrayBuffer(T *data, 
						const size_t size, 
						const ActionFile _typeAction = RETURN_DATA_WRITING_READING);
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
		};

		template<class T>
		inline ArrayBuffer<T>::ArrayBuffer(T *data, 
										   const size_t size, 
										   const ActionFile _typeAction) :
							   id(ARRAY_WITHOUT_INDEX),
							   element(data), 
							   bytes(sizeof(T) * size),
							   typeAction(_typeAction)
		{}

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

	PKG_END
RDPS_END

#endif//__ARRAY_BUFFER_H__