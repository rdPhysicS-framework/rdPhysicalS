#ifndef	__TO_PACK_OBJECTS_FOR_DEVICE_H__
#define	__TO_PACK_OBJECTS_FOR_DEVICE_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	
	FRWK_BEGIN
		class Light;
		class GeometricObject;
		class Camera;
		class ViewPlane;
		class Material;
		class Sampler;
	FRWK_END

	PKG_BEGIN 
		class Container; 
		struct RT_Material;
	PKG_END

	PDCT_BEGIN

		class PackerObjects;

		/********************************************************************************************************************************************
		 *
		 * Classe Referente ao estado do PackerObjects,
		 * Nela que ocorre o envio dos dados.
		 * Nela consiste:
		 * -> static State<PackerObjects> *INSTANCE: que eh uma referencia
		 *    dela mesmo, para facilitar o acesso e otimizar o processo evitando
		 *    inumeras instancias. 
		 *
		 ********************************************************************************************************************************************/
		class ToPackObjectsForDevice : public State<PackerObjects>
		{
		private:
			static State<PackerObjects> *INSTANCE;

		private:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor padrao
			 * privado pois só pode ter um instancia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ToPackObjectsForDevice();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para converter e empacotar os dados das
			 * luzes da cena para as luzes do pacote do container
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			void ToPackLightData(const FRWK Light *light, 
								 const PackerObjects &c);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para converter e empacotar os dados dos
			 * objetos da cena para os objetos do pacote do container
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			void ToPackObjectData(const FRWK GeometricObject *object,
								  const PackerObjects &c);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para converter e empacotar os dados do
			 * do material dos objetos da cena para o material dos objetos 
			 * do pacote do container
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			PKG RT_Material ToPackMaterialData(const FRWK Material *object);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para converter e empacotar os dados do
			 * camera da cena para a cameras do pacote do container
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			void ToPackCameraData(const FRWK Camera *object,
								  const PackerObjects &c);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para converter e empacotar os dados do
			 * da cena para os dados da cena ray tracing do pacote do container
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			void ToPackWordData(const PackerObjects &c);

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para converter e empacotar os dados do
			 * sampler para definir a qualidade da cena ray Tracing
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			void ToPackDataSampler(const const PackerObjects &c);

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrao destroi a instancia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~ToPackObjectsForDevice();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna|cria a instancia 
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			static State<PackerObjects> *Get();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para inicializacao dos dados do objeto que
			 * possui esse estado, quando entra neste estado
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Enter(const PackerObjects &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para execucao da funcao do estado
			 * (Chamar as funcoes auxiliares para Enpacotar os dados)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Execute(const PackerObjects &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para sair do estado (o que faz quando sai)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Exit(const PackerObjects &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para tratar as menssagens recebidas
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual bool OnMessage(const PackerObjects &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_PACK_OBJECTS_FOR_DEVICE_H__