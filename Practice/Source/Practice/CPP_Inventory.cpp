// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Inventory.h"
#include "Engine.h"

// Sets default values
ACPP_Inventory::ACPP_Inventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	MaxSlots = 10;
	Inventory.SetNum(MaxSlots);
}

// Called when the game starts or when spawned
void ACPP_Inventory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Inventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Inventory::PostInitProperties()
{
	Super::PostInitProperties();

}

void ACPP_Inventory::PostEditChangeProperty(FPropertyChangedEvent& ProperyChangedEvent)
{
	Super::PostEditChangeProperty(ProperyChangedEvent);
}

void ACPP_Inventory::PrintInfo()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Print Inventory Info");
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::FromInt(Inventory.Num()));
	for (int i = 0; i < MaxSlots; i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, Inventory[i].Name.ToString());
	}
}

// 비어있는 칸들 중 가장 앞쪽부터 채워넣음
void ACPP_Inventory::Add(FItemStruct Item)
{
	for (int i = 0; i < MaxSlots; i++)
	{
		if (Inventory[i].Name == "None")
		{
			Inventory[i] = Item;
			break;
		}
	}
}

void ACPP_Inventory::Set(int32 Index, FItemStruct Item)
{
	if (Index < MaxSlots)
	{
		if (Item.Count == 0)
		{
			Remove(Index);
		}
		else
		{
			Inventory[Index] = Item;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Set Inventory Failed: Index is out of range");
	}
}

void ACPP_Inventory::Remove(int32 Index)
{
	if (Index < MaxSlots)
	{
		Inventory[Index].Name = "None";
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Remove Inventory Failed: Index is out of range");
	}
}

void ACPP_Inventory::Get(int32 Index, bool& IsEmpty, FItemStruct& Item)
{
	IsEmpty = true;
	const TArray<FItemStruct>& arr = Inventory;
	if (Index < MaxSlots)
	{
		if (arr[Index].Name != "None")
		{
			IsEmpty = false;
			Item = arr[Index];
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Get Inventory Failed: Index is out of range");
	}
}

void ACPP_Inventory::SearchByName(FName Name, bool& IsFind, TArray<int32>& Indices, TArray<FItemStruct>& Items)
{
	IsFind = false;
	const TArray<FItemStruct>& arr = Inventory;
	for (int i = 0; i < arr.Num(); i++)
	{
		if (arr[i].Name == Name)
		{
			Indices.Add(i);
			Items.Add(arr[i]);
		}
	}
	if (Items.Num() > 0)
	{
		IsFind = true;
	}
}

void ACPP_Inventory::SearchByItemStruct(FItemStruct ItemStruct, bool& IsFind, TArray<int32>& Indices, TArray<FItemStruct>& Items)
{
	SearchByName(ItemStruct.Name, IsFind, Indices, Items);
}

void ACPP_Inventory::CheckEmptySlot(bool& IsEmpty)
{
	IsEmpty = false;
	for (int i = 0; i < MaxSlots; i++)
	{
		if (Inventory[i].Name == "None")
		{
			IsEmpty = true;
			break;
		}
	}
	
}

// IsSucceed = true이면 새로운 아이템 전부 인벤토리로 들어감. false이면 동일한 아이템이 인벤토리에 존재할 경우엔 최대 개수만큼 채우고 나머지는 반환.
void ACPP_Inventory::AddNewItem(FItemStruct ItemStruct, bool& IsSucceed, FItemStruct& _ItemStuct)
{
	IsSucceed = false;

	int32 ExtraCount;
	// For SearchByItemStruct
	bool IsFind;
	TArray<int32> Indices;
	TArray<FItemStruct> Items;
	// ItemStruct: New Items, Item: Same Item in Inventory
	SearchByItemStruct(ItemStruct, IsFind, Indices, Items);
	
	if (IsFind)
	{
		bool NewItemEmpty = false;
		for (int i = 0; i < Items.Num(); i++)
		{
			// 아이템 개수가 Max가 아닌 곳에 채워넣기
			ExtraCount = Items[i].MaxCount - Items[i].Count;
			if (ItemStruct.Count > ExtraCount)
			{
				Items[i].Count = Items[i].MaxCount;
				ItemStruct.Count -= ExtraCount;
			}
			else
			{
				Items[i].Count += ItemStruct.Count;
				ItemStruct.Count = 0;
			}

			// 갱신된 아이템 정보 반영
			Set(Indices[i], Items[i]);
			// 새로 추가될 아이템의 Count가 바닥나면 멈춤
			if (ItemStruct.Count == 0)
			{
				NewItemEmpty = true;
				break;
			}
			else if (ItemStruct.Count < 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "AddNewItem Err: ItemStruct.Count < 0");
			}
		}

		// 채워놓고 남은 것 처리
		if (NewItemEmpty == false)
		{
			bool IsEmpty;
			CheckEmptySlot(IsEmpty);
			if (IsEmpty)
			{
				// 나머지는 새로운 슬롯에 추가
				Add(ItemStruct);
				IsSucceed = true;
			}
			else
			{
				// 나머지는 반환
				_ItemStuct = ItemStruct;
			}
		}
		else
		{
			IsSucceed = true;
		}
	}
	else
	{
		bool IsEmpty;
		CheckEmptySlot(IsEmpty);
		if (IsEmpty)
		{
			// 나머지는 새로운 슬롯에 추가
			Add(ItemStruct);
			IsSucceed = true;
		}
		else
		{
			// 나머지는 반환
			_ItemStuct = ItemStruct;
		}
	}
}
