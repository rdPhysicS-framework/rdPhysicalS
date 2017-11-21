#ifndef	__PROGRAM_COMPONENETE_H__
#define	__PROGRAM_COMPONENETE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"
#include "../../GlobalDefs.h"

RDPS_BEGIN
	CL_BEGIN
		class ContextComponent;
		class DeviceComponent;
		class KernelComponent;
		/*************************************************************************************************
		*
		* Classe que contem a referencia do programa openCL,
		* para compilação do código que será executado no DISPOSITIVO
		*
		*************************************************************************************************/
		class ProgramComponent : public BaseClComponent<cl_program>
		{
		private:
			/*------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo os erros (se houver) 
			 * no código openCL. Informação do erro -11 do OpenCL, quando
			 * ocorrer este erro, utiliza-se essa função para mostrar os erros.
			 *------------------------------------------------------------------------------------------*/
			std::string GetBuidInfo(const DeviceComponent &device,
								    const cl_program_build_info paramName);

			/*--------------------------------------------------------------------------------------------
			 * Função auxiliar que cria o Programa OpenCL baseado no contexto e o retorna.
			 *--------------------------------------------------------------------------------------------*/
			cl_program CreateProgramWithSource(const ContextComponent &context,
							  const std::string source);

		public:
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a construção do programa utilizando um contexto
			 * já existente, e o adiciona a referencia do pai.
			 * O parametro source é o código do arquivo.cl que será executado
			 * na DISPOSITIVO.   
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent(const ContextComponent &context,
							 const std::string source       );
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona no a referencia um programa já contruido fora.
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent(const cl_program &program);
			/*------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent(const ProgramComponent &other);
			/*------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a função Release();
			 *------------------------------------------------------------------------------------------*/
			~ProgramComponent();
			/*------------------------------------------------------------------------------------------
			 * Destroi o programa
			 *------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();

			/*------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo as informações do programa.
			 *------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_program_info paramName);

			/*------------------------------------------------------------------------------------------
			 * Compila o código do arquivo .cl carregado para ser executado no DISPOSITIVO.
			 * O parametro options é para otimização no processo de bild para deixar um pouco
			 * mais leve.
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent &BuildProgram(const DeviceComponent &device,
										   const std::string &options = "");
			/*------------------------------------------------------------------------------------------
			 * Função de sobrecar de operadorga para cópia, chama a função de cópia do pai.
			 *------------------------------------------------------------------------------------------*/
			ProgramComponent &operator=(const ProgramComponent &other);
			//KernelComponent *CreateKernel(const std::string nameFunction);
			//void CreateKernels(std::vector<KernelComponent> &kernels);
		};

	CL_END
RDPS_END

#endif//__PROGRAM_COMPONENETE_H__