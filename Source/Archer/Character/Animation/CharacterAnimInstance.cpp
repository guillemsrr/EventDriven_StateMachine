#include "CharacterAnimInstance.h"

#include "Archer/Character/ArcherCharacter.h"
#include "Engine/SkeletalMeshSocket.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
	AimRotation = FRotator(90,0,0);
	SlotNames.Add(ECharacterAnimationSlots::FullBody, TEXT("FullBody"));
	SlotNames.Add(ECharacterAnimationSlots::UpperBody, TEXT("UpperBody"));
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<AArcherCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCharacterAnimInstance::PlayAnimationInSlot(UAnimSequence* AnimSequence, ECharacterAnimationSlots AnimationSlot)
{
	PlaySlotAnimationAsDynamicMontage(AnimSequence, SlotNames[AnimationSlot]);
}

void UCharacterAnimInstance::SetOrientationType(EOrientationType Orientation)
{
	OrientationType = Orientation;
	if(OrientationType == EOrientationType::Movement)
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	else
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		Character->SetActorRotation(FRotator(0, 0, 0));

		LastMovementOffsetYaw = 0;
		MovementOffsetYaw = 0;
		LastCharacterYaw = 0;
		CurrentCharacterYaw = 0;
		RootYawOffset = 0.f;
		RotationCurveLastFrame = 0.f;
		RotationCurve = 0.f;
		Pitch = 0;
	}
}

void UCharacterAnimInstance::UpdateAnimationProperties(float deltaTime)
{
	DeltaTime = deltaTime;

	if (!Character) return;

	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();
	IsMoving = Speed != 0.f;

	if(OrientationType == EOrientationType::AimDirection)
	{
		FRotator RootRotation = Character->GetAimRotator();
		RootRotation.Pitch = 0;
		RootRotation.Roll = 0;
		Character->SetActorRotation(RootRotation);
		
		USkeletalMeshSocket const* socket = Character->GetMesh()->GetSocketByName("spine_03Socket");
		
		AimRotation = Character->GetAimRotator();
		FRotator SocketRot = socket->GetSocketTransform(Character->GetMesh()).Rotator(); 

		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::White, TEXT("AimRotation: " + AimRotation.ToString()));

		MovementOffsetYaw = Character->GetAimRotationRelativeToMovement().Yaw;
		Pitch = AimRotation.Pitch;

		if (Speed > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}
		TurnInPlace();
	}
}

void UCharacterAnimInstance::CheckMovement()
{
	//Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
}

void UCharacterAnimInstance::TurnInPlace()
{
	if (!Character) return;

	if (Speed == 0)
	{
		LastCharacterYaw = CurrentCharacterYaw;
		CurrentCharacterYaw = Character->GetActorRotation().Yaw;

		const float YawDelta{CurrentCharacterYaw - LastCharacterYaw};

		//clamping [-180, 180]
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(RootYawOffset - YawDelta);

		//1.0 if turning, 0.0 if not
		const float Turning{GetCurveValue(TEXT("Turning"))};
		if (Turning > 0.f)
		{
			RotationCurveLastFrame = RotationCurve;
			RotationCurve = GetCurveValue(TEXT("Rotation"));
			const float DeltaRotation{RotationCurve - RotationCurveLastFrame};

			//turning left : right
			RootYawOffset > 0 ? RootYawOffset -= DeltaRotation : RootYawOffset += DeltaRotation;

			const float ABSRootYawOffset{FMath::Abs(RootYawOffset)};
			if (ABSRootYawOffset > 90.f)
			{
				const float YawExcess{ABSRootYawOffset - 90.F};
				RootYawOffset > 0 ? RootYawOffset -= YawExcess : RootYawOffset += YawExcess;
			}
		}
	}
	else
	{
		RootYawOffset = 0.f;
		CurrentCharacterYaw = Character->GetActorRotation().Yaw;
		LastCharacterYaw = CurrentCharacterYaw;
		RotationCurveLastFrame = 0.f;
		RotationCurve = 0.f;
	}
}
