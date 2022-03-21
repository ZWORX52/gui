#ifndef ORIGINS_H_INCLUDED
#define ORIGINS_H_INCLUDED

#include "main.h"

#include <string>
#include <vector>

class StringField {
	public:
		StringField(std::string, std::string);

		std::string name;
		std::string val;
};

class BoolField {
	public:
		BoolField(std::string, bool val);
		
		std::string name;
		bool val;
};

class IntField {
	public:
		IntField(std::string, int val);

		std::string name;
		bool val;
};

class FieldGroup {
	public:
		// Act as if these are all after each other - they will be in the output.
		std::vector<StringField> StringFields;
		std::vector<BoolField>   BoolFields;
		std::vector<IntField>    IntFields;

		FieldGroup();
};

enum PowerType {
	PowerType_None				= 0,
	// These todos are here because I haven't implemented those power types yet.
	// https://origins.readthedocs.io/en/latest/types/power_types/
	// Regular types
	PowerType_AttributeModifyTransfer	= 1,  // TODO
	PowerType_Attribute			= 2,  // TODO
	PowerType_Burn				= 3,  // TODO
	PowerType_Climbing			= 4,  // TODO
	PowerType_ConditionedAttribute		= 5,  // TODO
	PowerType_ConditionedRestrictArmor	= 6,  // TODO
	PowerType_Cooldown			= 7,  // TODO
	PowerType_CreativeFlight		= 8,  // TODO
	PowerType_DamageOverTime		= 9,  // TODO
	PowerType_DisableRegen			= 10, // TODO
	PowerType_EffectImmunity		= 11, // TODO
	PowerType_ElytraFlight			= 12, // TODO
	PowerType_EntityGlow			= 13, // TODO
	PowerType_EntityGroup			= 14, // TODO
	PowerType_Exhaust			= 15, // TODO
	PowerType_FireImmunity			= 16, // TODO
	PowerType_FireProjectile		= 17, // TODO
	PowerType_Freeze			= 18, // TODO
	PowerType_IgnoreWater			= 19, // TODO
	PowerType_Inventory			= 20, // TODO
	PowerType_Invisibility			= 21, // TODO
	PowerType_Invulnerability		= 22, // TODO
	PowerType_ItemOnItem			= 23, // TODO
	PowerType_KeepInventory			= 24, // TODO
	PowerType_Launch			= 25, // TODO
	PowerType_LavaVision			= 26, // TODO
	PowerType_ModelColor			= 27, // TODO
	PowerType_Multiple			= 28, // TODO
	PowerType_NightVision			= 29, // TODO
	PowerType_Overlay			= 30, // TODO
	PowerType_Particle			= 31, // TODO
	PowerType_Phasing			= 32, // TODO
	PowerType_Recipe			= 33, // TODO
	PowerType_Resource			= 34, // TODO
	PowerType_RestrictArmor			= 35, // TODO
	PowerType_SelfGlow			= 36, // TODO
	PowerType_Shader			= 37, // TODO
	PowerType_Shaking			= 38, // TODO
	PowerType_Simple			= 39, // TODO
	PowerType_StackingStatusEffect		= 40, // TODO
	PowerType_StartingEquipment		= 41, // TODO
	PowerType_StatusBarTexture		= 42, // TODO
	PowerType_Swimming			= 43, // TODO
	PowerType_ToggleNightVision		= 44, // TODO
	PowerType_Toggle			= 45, // TODO
	PowerType_Tooltip			= 46, // TODO
	PowerType_WalkOnFluid			= 47, // TODO
	// Action-related
	PowerType_ActionOnBeingUsed		= 48, // TODO
	PowerType_ActionOnBlockBreak		= 49, // TODO
	PowerType_ActionOnBlockUse		= 50, // TODO
	PowerType_ActionOnCallback		= 51, // TODO
	PowerType_ActionOnEntityUse		= 52, // TODO
	PowerType_ActionOnHit			= 53, // TODO
	PowerType_ActionOnItemUse		= 54, // TODO
	PowerType_ActionOnLand			= 55, // TODO
	PowerType_ActionOnWakeUp		= 56, // TODO
	PowerType_ActionOverTime		= 57, // TODO
	PowerType_ActionWhenDamageTaken		= 58, // TODO
	PowerType_ActionWhenHit			= 59, // TODO
	PowerType_ActiveSelf			= 60, // TODO
	PowerType_AttackerActionWhenHit		= 61, // TODO
	PowerType_SelfActionOnHit		= 62, // TODO
	PowerType_SelfActionOnKill		= 63, // TODO
	PowerType_SelfActionWhenHit		= 64, // TODO
	PowerType_TargetActionOnHit		= 65, // TODO
	// Modifying types
	PowerType_ModifyAirSpeed		= 66, // TODO
	PowerType_ModifyBlockRender		= 67, // TODO
	PowerType_ModifyBreakSpeed		= 68, // TODO
	PowerType_ModifyCameraSubmersion	= 69, // TODO
	PowerType_ModifyCrafting		= 70, // TODO
	PowerType_ModifyDamageDealt		= 71, // TODO
	PowerType_ModifyDamageTaken		= 72, // TODO
	PowerType_ModifyExhaustion		= 73, // TODO
	PowerType_ModifyFalling			= 74, // TODO
	PowerType_ModifyFluidRender		= 75, // TODO
	PowerType_ModifyFood			= 76, // TODO
	PowerType_ModifyHarvest			= 77, // TODO
	PowerType_ModifyJump			= 78, // TODO
	PowerType_ModifyLavaSpeed		= 79, // TODO
	PowerType_ModifyPlayerSpawn		= 80, // TODO
	PowerType_ModifyProjectileDamage	= 81, // TODO
	PowerType_ModifySlipperiness		= 82, // TODO
	PowerType_ModifyStatusEffectAmplifier	= 83, // TODO
	PowerType_ModifyStatusEffectDuration	= 84, // TODO
	PowerType_ModifySwimSpeed		= 85, // TODO
	PowerType_ModifyXPGain			= 86, // TODO
	// Preventing types
	PowerType_PreventBeingUsed		= 87, // TODO
	PowerType_PreventBlockSelection		= 88, // TODO
	PowerType_PreventBlockUse		= 89, // TODO
	PowerType_PreventDeath			= 90, // TODO
	PowerType_PreventElytraFlight		= 91, // TODO
	PowerType_PreventElytraCollision	= 92, // TODO
	PowerType_PreventEntityRender		= 93, // TODO
	PowerType_PreventEntityUse		= 94, // TODO
	PowerType_PreventFeatureRender		= 95, // TODO
	PowerType_PreventGameEvent		= 96, // TODO
	PowerType_PreventItemUse		= 97, // TODO
	PowerType_PreventSleep			= 98  // TODO
};

enum ActionType {
	ActionType_None				= 0,
	// I determine on a case-to-case basis which one has a longer name due to
	// expected usage
	// https://origins.readthedocs.io/en/latest/types/bientity_action_types/
	// Bi-entity
	ActionType_BiEntityAddVelocity		= 1,  // TODO
	ActionType_BiEntityDamage		= 2,  // TODO
	ActionType_Mount			= 3,  // TODO
	ActionType_SetInLove			= 4,  // TODO
	ActionType_Tame				= 5,  // TODO
	// Bi-entity meta
	ActionType_ActorAction			= 6,  // TODO
	ActionType_Invert			= 7,  // TODO
	ActionType_TargetAction			= 8,  // TODO
	// https://origins.readthedocs.io/en/latest/types/block_action_types/
	// Block
	ActionType_AddBlock			= 9,  // TODO
	ActionType_Bonemeal			= 10, // TODO
	ActionType_BlockExecuteCommand		= 11, // TODO
	ActionType_BlockExplode			= 12, // TODO
	ActionType_ModifyBlockState		= 13, // TODO
	ActionType_SetBlock			= 14, // TODO
	// Block meta
	ActionType_Offset			= 15, // TODO
	// https://origins.readthedocs.io/en/latest/types/entity_action_types/
	// Entity
	ActionType_AddVelocity			= 16, // TODO
	ActionType_AddXP			= 17, // TODO
	ActionType_ApplyEffect			= 18, // TODO
	ActionType_AreaOfEffect			= 19, // TODO
	ActionType_BlockActionAt		= 20, // TODO
	ActionType_ChangeResource		= 21, // TODO
	ActionType_ClearEffect			= 22, // TODO
	ActionType_CraftingTable		= 23, // TODO
	ActionType_Damage			= 24, // TODO
	ActionType_Dismount			= 25, // TODO
	ActionType_EmitGameEvent		= 26, // TODO
	ActionType_EnderChest			= 27, // TODO
	ActionType_EquippedItemAction		= 28, // TODO
	ActionType_ExecuteCommand		= 29, // TODO
	ActionType_Exhaust			= 30, // TODO
	ActionType_Explode			= 31, // TODO
	ActionType_Extinguish			= 32, // TODO
	ActionType_Feed				= 33, // TODO
	ActionType_GainAir			= 34, // TODO
	ActionType_Give				= 35, // TODO
	ActionType_GrantPower			= 36, // TODO
	ActionType_Heal				= 37, // TODO
	ActionType_PassengerAction		= 38, // TODO
	ActionType_PlaySound			= 39, // TODO
	ActionType_Raycast			= 40, // TODO
	ActionType_RevokePower			= 41, // TODO
	ActionType_RidingAction			= 42, // TODO
	ActionType_SetFallDistance		= 43, // TODO
	ActionType_SetOnFire			= 44, // TODO
	ActionType_SpawnEffectCloud		= 45, // TODO
	ActionType_SpawnEntity			= 46, // TODO
	ActionType_SpawnParticles		= 47, // TODO
	ActionType_SwingHand			= 48, // TODO
	ActionType_Toggle			= 49, // TODO
	ActionType_TriggerCooldown		= 50, // TODO
	// https://origins.readthedocs.io/en/latest/types/item_action_types/
	// Item
	ActionType_Consume			= 51, // TODO
	ActionType_ItemDamage			= 52, // TODO
	ActionType_Modify			= 53, // TODO
	// https://origins.readthedocs.io/en/latest/types/meta_action_types/
	// Meta
	ActionType_And				= 54, // TODO
	ActionType_Chance			= 55, // TODO
	ActionType_Choice			= 56, // TODO
	ActionType_Delay			= 57, // TODO
	ActionType_IfElseList			= 58, // TODO
	ActionType_IfElse			= 59, // TODO
	ActionType_Nothing			= 60  // TODO
};

enum ConditionType {
	ConditionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/bientity_condition_types/
	// Bi-entity
	ConditionType_AttackTarget		= 1,   // TODO
	ConditionType_BiEntityAttacker		= 2,   // TODO
	ConditionType_CanSee			= 3,   // TODO
	ConditionType_Distance			= 4,   // TODO
	ConditionType_Owner			= 5,   // TODO
	ConditionType_RelativeRotation		= 6,   // TODO
	ConditionType_BiEntityRidingRecursive	= 7,   // TODO
	ConditionType_BiEntityRidingRoot	= 8,   // TODO
	// Meta
	ConditionType_ActorCondition		= 10,  // TODO
	ConditionType_Both			= 11,  // TODO
	ConditionType_Either			= 12,  // TODO
	ConditionType_Invert			= 13,  // TODO
	ConditionType_TargetCondition		= 14,  // TODO
	ConditionType_Undirected		= 15,  // TODO
	// https://origins.readthedocs.io/en/latest/types/biome_condition_types/
	// Biome
	ConditionType_Category			= 16,  // TODO
	ConditionType_HighHumidity		= 17,  // TODO
	ConditionType_Precipitation		= 18,  // TODO
	ConditionType_Temperature		= 19,  // TODO
	// https://origins.readthedocs.io/en/latest/types/block_condition_types/
	// Block
	ConditionType_Adjacent			= 20,  // TODO
	ConditionType_Attachable		= 21,  // TODO
	ConditionType_BlastResistance		= 22,  // TODO
	ConditionType_BlockState		= 23,  // TODO
	ConditionType_Block			= 24,  // TODO
	ConditionType_DistanceFromCoordinatesBlk= 25,  // TODO
	ConditionType_BlockExposedToSky		= 26,  // TODO
	ConditionType_Fluid			= 27,  // TODO
	ConditionType_Hardness			= 28,  // TODO
	ConditionType_Height			= 29,  // TODO
	ConditionType_BlockInTag		= 30,  // TODO
	ConditionType_LightBlocking		= 31,  // TODO
	ConditionType_LightLevel		= 32,  // TODO
	ConditionType_Material			= 33,  // TODO
	ConditionType_MovementBlocking		= 34,  // TODO
	ConditionType_BlockNBT			= 35,  // TODO
	ConditionType_Replacable		= 36,  // TODO
	ConditionType_Slipperiness		= 37,  // TODO
	ConditionType_Waterloggable		= 38,  // TODO
	// Meta
	ConditionType_Offset			= 39,  // TODO
	// https://origins.readthedocs.io/en/latest/types/damage_condition_types/
	// Damage
	ConditionType_DamageAmount		= 40,  // TODO
	ConditionType_Attacker			= 41,  // TODO
	ConditionType_Fire			= 42,  // TODO
	ConditionType_Name			= 43,  // TODO
	ConditionType_Projectile		= 44,  // TODO
	// https://origins.readthedocs.io/en/latest/types/entity_condition_types/
	// Entity
	ConditionType_Ability			= 45,  // TODO
	ConditionType_Advancement		= 46,  // TODO
	ConditionType_Air			= 47,  // TODO
	ConditionType_Attribute			= 48,  // TODO
	ConditionType_Biome			= 49,  // TODO
	ConditionType_BlockCollision		= 50,  // TODO
	ConditionType_BlockInRadius		= 51,  // TODO
	ConditionType_Brightness		= 52,  // TODO
	ConditionType_Climbing			= 53,  // TODO
	ConditionType_CollidedHorizontally	= 54,  // TODO
	ConditionType_Command			= 55,  // TODO
	ConditionType_CreativeFlying		= 56,  // TODO
	ConditionType_Daytime			= 57,  // TODO
	ConditionType_Dimension			= 58,  // TODO
	ConditionType_DistanceFromCoordinates	= 59,  // TODO
	ConditionType_ElytraFlightPossible	= 60,  // TODO
	ConditionType_Enchantment		= 61,  // TODO
	ConditionType_EntityGroup		= 62,  // TODO
	ConditionType_EntityType		= 63,  // TODO
	ConditionType_EquippedItem		= 64,  // TODO
	ConditionType_Exists			= 65,  // TODO
	ConditionType_ExposedToSky		= 66,  // TODO
	ConditionType_ExposedToSun		= 67,  // TODO
	ConditionType_FallDistance		= 68,  // TODO
	ConditionType_FallFlying		= 69,  // TODO
	ConditionType_FluidHeight		= 70,  // TODO
	ConditionType_FoodLevel			= 71,  // TODO
	ConditionType_Gamemode			= 72,  // TODO
	ConditionType_Health			= 73,  // TODO
	ConditionType_InBlockAnywhere		= 74,  // TODO
	ConditionType_InBlock			= 75,  // TODO
	ConditionType_InRain			= 76,  // TODO
	ConditionType_InTag			= 77,  // TODO
	ConditionType_Invisible			= 78,  // TODO
	ConditionType_Living			= 79,  // TODO
	ConditionType_Moving			= 80,  // TODO
	ConditionType_NBT			= 81,  // TODO
	ConditionType_OnBlock			= 82,  // TODO
	ConditionType_OnFire			= 83,  // TODO
	ConditionType_Origin			= 84,  // TODO
	ConditionType_PassengerRecursive	= 85,  // TODO
	ConditionType_Passenger			= 86,  // TODO
	ConditionType_PowerActive		= 87,  // TODO
	ConditionType_PowerType			= 88,  // TODO
	ConditionType_Power			= 89,  // TODO
	ConditionType_Predicate			= 90,  // TODO
	ConditionType_Raycast			= 91,  // TODO
	ConditionType_RelativeHealth		= 92,  // TODO
	ConditionType_Resource			= 93,  // TODO
	ConditionType_RidingRecursive		= 94,  // TODO
	ConditionType_RidingRoot		= 95,  // TODO
	ConditionType_Riding			= 96,  // TODO
	ConditionType_SaturationLevel		= 97,  // TODO
	ConditionType_Scoreboard		= 98,  // TODO
	ConditionType_Sneaking			= 99,  // TODO
	ConditionType_Sprinting			= 100, // TODO
	ConditionType_StatusEffect		= 101, // TODO
	ConditionType_SubmergedIn		= 102, // TODO
	ConditionType_Swimming			= 103, // TODO
	ConditionType_Tamed			= 104, // TODO
	ConditionType_TimeOfDay			= 105, // TODO
	ConditionType_UsingEffectiveTool	= 106, // TODO
	ConditionType_UsingItem			= 107, // TODO
	ConditionType_XPLevels			= 108, // TODO
	ConditionType_XPPoints			= 109, // TODO
	// https://origins.readthedocs.io/en/latest/types/fluid_condition_types/
	// Fluid
	ConditionType_EmptyFluid		= 110, // TODO
	ConditionType_FluidInTag		= 111, // TODO
	ConditionType_Still			= 112, // TODO
	// https://origins.readthedocs.io/en/latest/types/item_condition_types/
	// Item
	ConditionType_Amount			= 113, // TODO
	ConditionType_ArmorValue		= 114, // TODO
	ConditionType_Empty			= 115, // TODO
	ConditionType_ItemEnchantment		= 116, // TODO
	ConditionType_Fireproof			= 117, // TODO
	ConditionType_Food			= 118, // TODO
	ConditionType_HarvestLevel		= 119, // TODO
	ConditionType_Ingredient		= 120, // TODO
	ConditionType_Meat			= 121, // TODO
	ConditionType_ItemNBT			= 122, // TODO
	ConditionType_Smeltable			= 123, // TODO
	// https://origins.readthedocs.io/en/latest/types/meta_condition_types/
	// Meta
	ConditionType_And			= 124, // TODO
	ConditionType_Constant			= 125, // TODO
	ConditionType_Not			= 126, // TODO
	ConditionType_Or			= 127  // TODO
};

#endif//ORIGINS_H_INCLUDED

