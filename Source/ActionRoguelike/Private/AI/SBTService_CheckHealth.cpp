// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		AAIController* AIC = OwnerComp.GetAIOwner();
		if (ensure(AIC))
		{
			APawn* MyPawn = AIC->GetPawn();
			if (ensure(MyPawn))
			{
				USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(MyPawn);
				if (ensure(AttributeComp))
				{
					float bLowHealth = (AttributeComp->GetHealth() / AttributeComp->GetHealthMax()) < LowHealthFraction;

					BlackboardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
				}
			}
		}
	}
}
