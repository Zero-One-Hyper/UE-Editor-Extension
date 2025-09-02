// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorJsonTool.h"
#include "Policies/JsonPrintPolicy.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "JsonObjectConverter.h"

EditorJsonTool::EditorJsonTool()
{
}

EditorJsonTool::~EditorJsonTool()
{
}


void EditorJsonTool::SaveJsonObject(TSharedPtr<FBaseSerializedJsonObject> SerializedJsonObject, FString JsonName)
{
	FString JsonString = TEXT("");
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter =
		TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	JsonWriter->WriteObjectStart();
	//填入序列化
	SerializedJsonObject->SerializeObject(JsonWriter);

	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	FString FilePath = FPaths::ProjectSavedDir() / TEXT("JsonOutPut") / JsonName + TEXT(".json");
	if (FFileHelper::SaveStringToFile(JsonString, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogTemp, Display, TEXT("Json 文件保存成功 路径：%s"), *FilePath);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Json 文件保存失败"));
	}
}
