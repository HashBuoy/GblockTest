// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/GBSimpleRandomMovementTrait.h"


#include "MassEntityTemplateRegistry.h" 

void UGBSimpleRandomMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddFragment<FSimpleMovementFragment>();
}
