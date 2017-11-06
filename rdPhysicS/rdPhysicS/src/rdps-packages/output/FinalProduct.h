#ifndef	__FINAL_PRODUCT_H__
#define	__FINAL_PRODUCT_H__

#include "..\..\GlobalDefs.h"
#include "..\ArrayBuffer.h"
#include "..\..\Util\LogError.h"

RDPS_BEGIN
	PKG_BEGIN
	/********************************************************************************************************************************************
	 *
	 * Classe responsavel em armazenar o resultado dos dados finais calculados
	 * no dispositivo openCL.
	 * Nela Contem:
	 * -> Um ponteiro para os dados que serão lidos da memória do dispositivo;
	 * -> A quantidade de elementos no array;
	 * -> E o array buffer, para envio do array para o despositivo, com a função
	 *    de leitura de dados.
	 *
	 ********************************************************************************************************************************************/
		template<class T>
		class FinalProduct
		{
		private:
			T *data;
			size_t size;
			ArrayBuffer<T> *buffer;

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor. 
			 * Cria o ArrayBuffer e o define como
			 * função de leitura de dados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor que recebe como parametro
			 * o tamanho do array para ser alocado na memória. 
			 * Cria o ArrayBuffer e o define como
			 * função de leitura de dados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct(const size_t _size);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor de copia.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct(const FinalProduct<T> &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~FinalProduct();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * sobrecarga de operador para copia de dados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct<T> &operator=(const FinalProduct<T> &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para alocar o array na memoria,
			 * com base no tamanho passdo por parametro.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct<T> &CreateData(const size_t _size);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o array de resultados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline T *GetData() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna o ArrayBuffer.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			inline ArrayBuffer<T> *GetBuffer() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que da o comando de 
			 * atualizacao e envio das dados do ArrayBuffer no dispositivo.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct<T> &Update();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que da o comando de
			 * envio dos dados do ArrayBuffer para o dispositivo.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct<T> &ToSend();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que da o comando de
			 * leitura dos dados no dispositivo para o array de dados final.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct<T> &ApplyBuffer();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que destroi os dados
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			FinalProduct<T> &DestroyData();
		};

		template<class T>
		inline FinalProduct<T>::FinalProduct() :
								data(nullptr),
								size(0),
								buffer(new ArrayBuffer<T>(
									   RETURN_DATA_READING))
		{}

		template<class T>
		inline FinalProduct<T>::FinalProduct(const size_t _size) :
			data(new T[_size]),
			size(_size),
			buffer(new ArrayBuffer<T>(data, _size, 
								RETURN_DATA_READING))
		{}

		template<class T>
		inline FinalProduct<T>::FinalProduct(const FinalProduct<T> &other) :
								data(nullptr),
								size(other.size),
								buffer(other.buffer)
		{
			memcpy(data, (void*)other.data, sizeof(T)*other.size);
		}

		template<class T>
		inline FinalProduct<T>::~FinalProduct()
		{
			if (data)
				delete data;
			delete buffer;
		}

		template<class T>
		inline FinalProduct<T> &FinalProduct<T>::operator=(const FinalProduct<T> &other)
		{
			if (data)
				delete data;
			memcpy(data, (void*)other.data, sizeof(T)*other.size);
			size = other.size;
			buffer = other.buffer;

			return (*this);
		}

		template<class T>
		inline FinalProduct<T> &FinalProduct<T>::CreateData(const size_t _size)
		{
			if (!data)
			{
				data = new T[_size];
				size = _size;
				Update();
			}
			else
			{
				Logger::Log("The final array has already been created. To create new data destroy it.");
			}

			return (*this);
		}

		template<class T>
		inline T *FinalProduct<T>::GetData() const
		{
			return data;
		}

		template<class T>
		inline ArrayBuffer<T>* FinalProduct<T>::GetBuffer() const
		{
			return buffer;
		}

		template<class T>
		inline FinalProduct<T> &FinalProduct<T>::Update()
		{
			buffer->UpdateData(data, size);
			return (*this);
		}

		template<class T>
		inline FinalProduct<T> &FinalProduct<T>::ToSend()
		{
			buffer->Binding();
			return (*this);
		}

		template<class T>
		inline FinalProduct<T> &FinalProduct<T>::ApplyBuffer()
		{
			buffer->Apply();
			return (*this);
		}

		template<class T>
		inline FinalProduct<T> &FinalProduct<T>::DestroyData()
		{
			if (data)
			{
				delete data;
				size = 0;
				buffer->DestroyElement();
			}

			return (*this);
		}

	PKG_END
RDPS_END


#endif//__FINAL_PRODUCT_H__

