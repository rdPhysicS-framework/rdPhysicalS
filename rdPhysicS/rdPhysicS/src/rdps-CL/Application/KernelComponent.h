#ifndef	__KERNEL_COMPONENTE_H__
#define	__KERNEL_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"
#include "..\..\Util\LogError.h"
#include "MemObjectComponent.h"

RDPS_BEGIN
	CL_BEGIN
		class DeviceComponent;
		class ProgramComponent;
		/************************************************************************************************
		 *
		 * Classe que contem o kernel referente a fun��o principal(main) que ser� executada
		 * na DISPOSITIVO
		 *
		 ************************************************************************************************/
		class KernelComponent : public BaseClComponent<cl_kernel>
		{
		private:
			/*--------------------------------------------------------------------------------------------
			* Fun��o auxiliar que cria o Kernel baseado no programa OpenCL e o retorna.
			*--------------------------------------------------------------------------------------------*/
			cl_kernel Create(const ProgramComponent &program,
							 const std::string &name);

		public:
			/*-------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *--------------------------------------------------------------------------------------------*/
			KernelComponent();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a constru��o do kernel utilizando um  programa j� criado.
			 * O parametro name, � o nome da fun��o principal(main) que ser� excutada na DISPOSITIVO.
			 *------------------------------------------------------------------------------------------*/
			KernelComponent(const ProgramComponent &program,
							const std::string &name          );
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_kernel j� construido fora.
			 *--------------------------------------------------------------------------------------------*/
			KernelComponent(const cl_kernel &kernel);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			KernelComponent(const KernelComponent &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *--------------------------------------------------------------------------------------------*/
			~KernelComponent();
			/*--------------------------------------------------------------------------------------------
			 * Destroi o kernel.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();

			/*--------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo as informa��es do Kernel.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_kernel_info paramName);
			
			size_t *GetKernelWorkGroupInfo(const DeviceComponent &device,
										   const cl_kernel_work_group_info paramName);
			
			/*--------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo as informa��es de grupos de trabalhos do kernel.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const DeviceComponent &device,
								const cl_kernel_work_group_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Fun��o auxiliar, que adiciona todos os argumentos da fun��o
			 * principal, que ser� executada na DISPOSITIVO.
			 * O parametro index � o indice referente na lista de argumentos da
			 * fun��o kernel. O template T, � o objeto de mem�rio(MemObjectComponent) referente ao dado
			 * que ser� passado. Gen�rico por que na fun��o kernel poder conter um parametro
			 * c�pia, neste caso ao inves de passar o objeto referencia(MemObjectComponent), passa-se
			 * a vari�vel do pr�prio dado.
			 *--------------------------------------------------------------------------------------------*/
			template<typename T>
			inline KernelComponent &SetArgument(int index, T obj);

			KernelComponent &SetArgument(uint index, const void *data, const size_t bytes);

			/*--------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operador para c�pia, chama a fun��o de c�pia do pai.
			 *--------------------------------------------------------------------------------------------*/
			KernelComponent &operator=(const KernelComponent &other);
		};

		template<typename T>
		inline KernelComponent &KernelComponent::SetArgument(int index, T obj)
		{
			int status = clSetKernelArg(object, index, sizeof(T), (void*)&obj);

			if (status != CL_SUCCESS)
			{
				Logger::Log("ERROR when setting the argument " + std::to_string(index)
							+ "\nERROR: " + std::to_string(status));
				
			}

			return (*this);
		}

	RDPS_END
CL_END
#endif//__KERNEL_COMPONENTE_H__