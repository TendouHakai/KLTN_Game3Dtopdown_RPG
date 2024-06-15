// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

void ACoin::BeginPlay()
{
	Super::BeginPlay();

	TargetCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ACoin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsValid(TargetCharacter))
		UpdateState(DeltaSeconds);
}

void ACoin::Emit(FVector EmitVel, FRotator RotVel)
{
	TargetCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();

	EmitVel = EmitVel + FMath::VRand() * (EmitVel.Size() * 0.2f);

	velocity_ = EmitVel;
	rot_vel_ = RotVel;
	BountCnt = 0;
	Speed = 1.0f;

	SetState(EDropState::DROP);
}

void ACoin::SetState(EDropState state)
{
	if (state_ != EDropState::CHASE_PICKUP && state == EDropState::CHASE_PICKUP)
		OnCoinStartChase();

	state_ = state;
}

void ACoin::UpdateState(float delta_seconds)
{
	switch (state_)
	{
	case EDropState::DROP:
		StateDropping(delta_seconds);
		break;
	case EDropState::CHASE_PICKUP:
		StateSucking(delta_seconds);
		break;
	}
}

void ACoin::StateDropping(float delta_seconds)
{
	FVector gravity = FVector(0, 0, -3000);
	velocity_ += gravity * delta_seconds;
	FVector pos_now = GetActorLocation();
	FVector pos_next = GetActorLocation() + velocity_ * delta_seconds;

	if (bRotOnDrop)
	{
		FRotator RotNext;
		RotNext.Roll = GetActorRotation().Roll + rot_vel_.Roll * delta_seconds;
		RotNext.Yaw = GetActorRotation().Yaw + rot_vel_.Yaw * delta_seconds;
		RotNext.Pitch = GetActorRotation().Pitch + rot_vel_.Pitch * delta_seconds;
		SetActorRelativeRotation(RotNext);
	}

	FHitResult Hit(ForceInit);
	if (GetWorld()->LineTraceSingleByObjectType(
		Hit,
		pos_now,
		pos_next,
		FCollisionObjectQueryParams(FCollisionObjectQueryParams::AllStaticObjects),
		FCollisionQueryParams::DefaultQueryParam
	)
		)
	{
		BountCnt++;
		pos_next = GetActorLocation();	

		const int32 MaxBoundCnt = 2;

		if (BountCnt >= MaxBoundCnt)
		{
			float MAX_COIN_DISTANCE = 2000;
			float Distance = FVector::Dist(TargetCharacter->GetActorLocation(), GetActorLocation());

			if (Distance < MAX_COIN_DISTANCE)
			{
				SetState(EDropState::CHASE_PICKUP);
				return;
			}
			else
			{
				OnCoinPicked.Broadcast(this);
			}
		}

		float REFLECTANCE = 800;
		velocity_ = Hit.Normal * REFLECTANCE;
	}

	SetActorLocation(pos_next);
}

void ACoin::StateSucking(float delta_seconds)
{
	FVector distance = TargetCharacter->GetActorLocation() - GetActorLocation();
	FVector dir = distance.GetSafeNormal();

	float vel = 1600;
	FVector pos_next = GetActorLocation() + (dir * vel) * delta_seconds * Speed;
	Speed *= (1.0f + delta_seconds);

	SetActorLocation(pos_next);

	if (IsPickUp())
		OnCoinPicked.Broadcast(this);
}

bool ACoin::IsPickUp()
{
	float distance = FVector::Dist(TargetCharacter->GetActorLocation(), GetActorLocation());
	if (distance < 80)
		return true;
	return false;
}
