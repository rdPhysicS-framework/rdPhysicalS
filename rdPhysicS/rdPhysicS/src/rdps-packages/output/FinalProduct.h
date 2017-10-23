#ifndef	__FINAL_PRODUCT_H__
#define	__FINAL_PRODUCT_H__

#include "..\..\GlobalDefs.h"
#include "..\ArrayBuffer.h"
#include "..\..\rdps-CL\Util\LogError.h"

RDPS_BEGIN
	PKG_BEGIN
		
		template<class T>
		class FinalProduct
		{
		private:
			T *data;
			size_t size;
			ArrayBuffer<T> *buffer;

		public:
			FinalProduct();
			FinalProduct(const size_t _size);
			FinalProduct(const FinalProduct<T> &other);
			~FinalProduct();

			FinalProduct<T> &operator=(const FinalProduct<T> &other);

			FinalProduct<T> &CreateData(const size_t _size);
			inline T *GetData() const;
			inline ArrayBuffer<T> *GetBuffer() const;
			FinalProduct<T> &Update();
			FinalProduct<T> &ToSend();
			FinalProduct<T> &ApplyBuffer();
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

