// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportLevel.h"

// Sets default values
ATeleportLevel::ATeleportLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleportLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

