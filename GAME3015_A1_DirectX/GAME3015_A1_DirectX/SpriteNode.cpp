#include "SpriteNode.h"
#include "Game.hpp"
#include "State.hpp"

SpriteNode::SpriteNode(State* state) : Entity(state)
{
}


void SpriteNode::drawCurrent() const
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	Game* game = mState->getContext()->game;

	auto objectCB = game->mCurrFrameResource->ObjectCB->Resource();
	auto matCB = game->mCurrFrameResource->MaterialCB->Resource();

	if (mSpriteNodeRitem != nullptr)
	{
		game->getCmdList()->IASetVertexBuffers(0, 1, &mSpriteNodeRitem->Geo->VertexBufferView());
		game->getCmdList()->IASetIndexBuffer(&mSpriteNodeRitem->Geo->IndexBufferView());
		game->getCmdList()->IASetPrimitiveTopology(mSpriteNodeRitem->PrimitiveType);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(game->mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(mSpriteNodeRitem->Mat->DiffuseSrvHeapIndex, game->mCbvSrvDescriptorSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + mSpriteNodeRitem->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + mSpriteNodeRitem->Mat->MatCBIndex * matCBByteSize;

		game->getCmdList()->SetGraphicsRootDescriptorTable(0, tex);
		game->getCmdList()->SetGraphicsRootConstantBufferView(1, objCBAddress);
		game->getCmdList()->SetGraphicsRootConstantBufferView(3, matCBAddress);

		game->getCmdList()->DrawIndexedInstanced(mSpriteNodeRitem->IndexCount, 1, mSpriteNodeRitem->StartIndexLocation, mSpriteNodeRitem->BaseVertexLocation, 0);
	}

}

void SpriteNode::buildCurrent()
{
	Game* game = mState->getContext()->game;

	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	renderer->ObjCBIndex = (UINT) mState->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mMat].get(); //"Desert"
	renderer->Geo = game->getGeometries()[mGeo].get(); //"boxGeo"
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs[mDrawName].IndexCount; //"box"
	renderer->StartIndexLocation = renderer->Geo->DrawArgs[mDrawName].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs[mDrawName].BaseVertexLocation;
	mSpriteNodeRitem = render.get();
	mState->getRenderItems().push_back(std::move(render));
}

void SpriteNode::SetMatGeoDrawName(std::string Mat, std::string Geo, std::string DrawName)
{
	mMat = Mat;
	mGeo = Geo;
	mDrawName = DrawName;
}

