#ifndef	__GENERAL_MANAGER_H__
#define	__GENERAL_MANAGER_H__

#include "..\base\Entity.h"
#include <map>

RDPS_BEGIN
	PDCT_BEGIN
		
		class Collaborator;

		class GeneralManager : public Entity
		{
		private:
			std::map<CollaboratorsFunction, 
					 Collaborator*> collaborators;

			static GeneralManager *INSTANCE;
		private:
			GeneralManager();

		public:
			GeneralManager(const GeneralManager &other);
			~GeneralManager();

			static GeneralManager *Get();

			const Collaborator
				*GetCollaborator(const CollaboratorsFunction function);

			const std::map<CollaboratorsFunction, Collaborator*>
				&GetCollaborators() const;

			GeneralManager &AddCollaborator(CollaboratorsFunction function,
											Collaborator *collaborator);

			GeneralManager &RemoveCollaborator(CollaboratorsFunction function,
											   Collaborator *collaborator);

			GeneralManager *Clone();
			virtual GeneralManager &ExecuteFunction();
			virtual bool HandleMessage(const Message &message);
		};

	PDCT_END
RDPS_END

#endif//__GENERAL_MANAGER_H__