// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorJsonClasses.h"

void FFactoryEquipmentsDataList::SerializeObject(
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	//列表的序列化
	Writer->WriteArrayStart(TEXT("AllDatas"));
	for (auto data : AllFactoryEquipmentsDatas)
	{
		data->SerializeObject(Writer);
	}
	Writer->WriteArrayEnd();
}

void FFactoryEquipmentsDataList::FFactoryEquipmentsData::SerializeObject(
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart();
	Writer->WriteValue(TEXT("Name"), this->Name);
	FString ActorLocation = FString::Printf(TEXT("(X=%f,Y=%f,Z=%f)"),
	                                        this->Position.X, this->Position.Y, this->Position.Z);
	Writer->WriteValue(TEXT("Location"), ActorLocation);
	Writer->WriteValue(TEXT("Rotation"), TEXT("(X=0,Y=-10,Z=-50)"));
	Writer->WriteValue(TEXT("Length"), TEXT("500"));
	Writer->WriteObjectEnd();
}
