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
		 * Classe que contem o kernel referente a função principal(main) que será executada
		 * na DISPOSITIVO
		 *
		 ************************************************************************************************/
		class KernelComponent : public BaseClComponent<cl_kernel>
		{
		private:
			/*--------------------------------------------------------------------------------------------
			* Função auxiliar que cria o Kernel baseado no programa OpenCL e o retorna.
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
			 * Ocorre a construção do kernel utilizando um  programa já criado.
			 * O parametro name, é o nome da função principal(main) que será excutada na DISPOSITIVO.
			 *------------------------------------------------------------------------------------------*/
			KernelComponent(const ProgramComponent &program,
							const std::string &name          );
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_kernel já construido fora.
			 *--------------------------------------------------------------------------------------------*/
			KernelComponent(const cl_kernel &kernel);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *--------------------------------------------------------------------------------------------*/
			KernelComponent(const KernelComponent &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a função Release();
			 *--------------------------------------------------------------------------------------------*/
			~KernelComponent();
			/*--------------------------------------------------------------------------------------------
			 * Destroi o kernel.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();

			/*--------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo as informações do Kernel.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_kernel_info paramName);
			
			size_t *GetKernelWorkGroupInfo(const DeviceComponent &device,
										   const cl_kernel_work_group_info paramName);
			
			/*--------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo as informações de grupos de trabalhos do kernel.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const DeviceComponent &device,
								const cl_kernel_work_group_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Função auxiliar, que adiciona todos os argumentos da função
			 * principal, que será executada na DISPOSITIVO.
			 * O parametro index é o indice referente na lista de argumentos da
			 * função kernel. O template T, é o objeto de memório(MemObjectComponent) referente ao dado
			 * que será passado. Genérico por que na função kernel poder conter um parametro
			 * cópia, neste caso ao inves de passar o objeto referencia(MemObjectComponent), passa-se
			 * a variável do próprio dado.
			 *--------------------------------------------------------------------------------------------*/
			template<typename T>
			inline KernelComponent &SetArgument(int index, T obj);

			KernelComponent &SetArgument(uint index, const void *data, const size_t bytes);

			/*--------------------------------------------------------------------------------------------
			 * Função de sobrecar de operador para cópia, chama a função de cópia do pai.
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