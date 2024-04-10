// Fill out your copyright notice in the Description page of Project Settings.


#include "Game3DtopdownRPG/Battle/CheatableController.h"

void ACheatableController::ExcuteAdditionProcDelegate()
{
	AdditionProc_Delegate.Broadcast();
}
