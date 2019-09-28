//#include "SpriteFactory.h"
//
//SpriteFactory* SpriteFactory::__instance = NULL;
//
//void SpriteFactory::LoadResources()
//{
//	auto sprites = SpriteFactory::GetInstance();
//	// ======================== PLAYER SPRITE ===========================
//	sprites->AddSprite(new PlayerSprite(STANDING, 0, 5, 22, 38));
//	sprites->AddSprite(new PlayerSprite(RUNNING, 338, 5, 360, 38));
//	sprites->AddSprite(new PlayerSprite(RUNNING, 368, 5, 390, 38));
//	sprites->AddSprite(new PlayerSprite(RUNNING, 400, 5, 422, 38));
//	sprites->AddSprite(new PlayerSprite(SITTING, 2, 53, 21, 76));
//	sprites->AddSprite(new PlayerSprite(JUMPING, 139, 50, 163, 78));
//	sprites->AddSprite(new PlayerSprite(JUMPING, 165, 50, 189, 78));
//	sprites->AddSprite(new PlayerSprite(JUMPING, 190, 50, 214, 78));
//	sprites->AddSprite(new PlayerSprite(JUMPING, 216, 50, 240, 78));
//	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 40, 5, 62, 38));
//	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 66, 5, 93, 38));
//	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 110, 5, 133, 38));
//	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 35, 53, 57, 76));
//	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 58, 53, 82, 76));
//	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 100, 53, 122, 76));
//	sprites->AddSprite(new PlayerSprite(CLINGING, 264, 5, 288, 38));
//	sprites->AddSprite(new PlayerSprite(CLIMBING, 286, 5, 310, 38));
//
//}
//// Thêm một Sprite vào danh sách các Sprite, quy định theo Tag của Sprite
//void SpriteFactory::Add(LPSPRITE sprite)
//{
//	sprites[sprite].push_back(sprite);
//}
//
//Sprite* SpriteFactory::GetSprite(Tag tag, int index)
//{
//	return _sprites[tag][index];
//}
//
//// Lấy các Sprite (dùng cho tạo Animation) theo Tag từ vị trí first->last
//std::vector<Sprite*> SpriteFactory::GetSprites(Tag tag, int firstIndex, int lastIndex)
//{
//	auto first = _sprites[tag].begin() + firstIndex;
//	auto last = _sprites[tag].begin() + lastIndex;
//	return std::vector<Sprite*>(first, last + 1);
//}
//
//SpriteFactory* SpriteFactory::GetInstance()
//{
//	if (__instance == NULL)
//		__instance = new SpriteFactory();
//	return __instance;
//}
//
