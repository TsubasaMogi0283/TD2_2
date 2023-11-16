#include "CreateMaterial.h"
#include <Math/Matrix/Calculation/Matrix4x4Calculation.h>


void CreateMaterial::Initialize(){
	materialResource_=DirectXSetup::GetInstance()->CreateBufferResource(sizeof(Material)).Get();

}

void CreateMaterial::SetInformation(Vector4 setColor){
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->color = setColor;
	materialData_->enableLighting=false;

	materialData_->uvTransform = MakeIdentity4x4();

	materialResource_->Unmap(0, nullptr);
}


void CreateMaterial::SetGraphicsCommand(){
	

	DirectXSetup::GetInstance()->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());


}


