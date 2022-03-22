#ifndef ORIGINS_HPP_INCLUDED
#define ORIGINS_HPP_INCLUDED

#include "main.hpp"

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
};

enum ActionPowerType {
	ActionPowerType_None			= 0,
	// Action-related
	PowerType_ActionOnBeingUsed		= 1,  // TODO
	PowerType_ActionOnBlockBreak		= 2,  // TODO
	PowerType_ActionOnBlockUse		= 3,  // TODO
	PowerType_ActionOnCallback		= 4,  // TODO
	PowerType_ActionOnEntityUse		= 5,  // TODO
	PowerType_ActionOnHit			= 6,  // TODO
	PowerType_ActionOnItemUse		= 7,  // TODO
	PowerType_ActionOnLand			= 8,  // TODO
	PowerType_ActionOnWakeUp		= 9,  // TODO
	PowerType_ActionOverTime		= 10, // TODO
	PowerType_ActionWhenDamageTaken		= 11, // TODO
	PowerType_ActionWhenHit			= 12, // TODO
	PowerType_ActiveSelf			= 13, // TODO
	PowerType_AttackerActionWhenHit		= 14, // TODO
	PowerType_SelfActionOnHit		= 15, // TODO
	PowerType_SelfActionOnKill		= 16, // TODO
	PowerType_SelfActionWhenHit		= 17, // TODO
	PowerType_TargetActionOnHit		= 18  // TODO
};

enum ModifyPowerType {
	ModifyPowerType_None			= 0,
	// Modifying types
	ModifyowerType_AirSpeed			= 1,  // TODO
	ModifyowerType_BlockRender		= 2,  // TODO
	ModifyowerType_BreakSpeed		= 3,  // TODO
	ModifyowerType_CameraSubmersion		= 4,  // TODO
	ModifyowerType_Crafting			= 5,  // TODO
	ModifyowerType_DamageDealt		= 6,  // TODO
	ModifyowerType_DamageTaken		= 7,  // TODO
	ModifyowerType_Exhaustion		= 8,  // TODO
	ModifyowerType_Falling			= 9,  // TODO
	ModifyowerType_FluidRender		= 10, // TODO
	ModifyowerType_Food			= 11, // TODO
	ModifyowerType_Harvest			= 12, // TODO
	ModifyowerType_Jump			= 13, // TODO
	ModifyowerType_LavaSpeed		= 14, // TODO
	ModifyowerType_PlayerSpawn		= 15, // TODO
	ModifyowerType_ProjectileDamage		= 16, // TODO
	ModifyowerType_Slipperiness		= 17, // TODO
	ModifyowerType_StatusEffectAmplifier	= 18, // TODO
	ModifyowerType_StatusEffectDuration	= 19, // TODO
	ModifyowerType_SwimSpeed		= 20, // TODO
	ModifyowerType_XPGain			= 21  // TODO
};

enum PreventPowerType {
	PreventPowerType_None			= 0,
	// Preventing types
	PreventPowerType_BeingUsed		= 1,  // TODO
	PreventPowerType_BlockSelection		= 2,  // TODO
	PreventPowerType_BlockUse		= 3,  // TODO
	PreventPowerType_Death			= 4,  // TODO
	PreventPowerType_ElytraFlight		= 5,  // TODO
	PreventPowerType_ElytraCollision	= 6,  // TODO
	PreventPowerType_EntityRender		= 7,  // TODO
	PreventPowerType_EntityUse		= 8,  // TODO
	PreventPowerType_FeatureRender		= 9,  // TODO
	PreventPowerType_GameEvent		= 10, // TODO
	PreventPowerType_ItemUse		= 11, // TODO
	PreventPowerType_Sleep			= 12  // TODO
};

enum BiEntityActionType {
	BiEntityActionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/bientity_action_types/
	// Bi-entity
	BiEntityActionType_AddVelocity		= 1,  // TODO
	BiEntityActionType_Damage		= 2,  // TODO
	BiEntityActionType_Mount		= 3,  // TODO
	BiEntityActionType_SetInLove		= 4,  // TODO
	BiEntityActionType_Tame			= 5,  // TODO
	// Bi-entity meta
	BiEntityActionType_ActorAction		= 6,  // TODO
	BiEntityActionType_Invert		= 7,  // TODO
	BiEntityActionType_TargetAction		= 8   // TODO
};

enum BlockActionType {
	BlockActionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/block_action_types/
	// Block
	BlockActionType_AddBlock		= 1, // TODO
	BlockActionType_Bonemeal		= 2, // TODO
	BlockActionType_ExecuteCommand		= 3, // TODO
	BlockActionType_Explode			= 4, // TODO
	BlockActionType_ModifyBlockState	= 5, // TODO
	BlockActionType_SetBlock		= 6, // TODO
	// Block meta
	BlockActionType_Offset			= 7  // TODO
};

enum EntityActionType {
	EntityActionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/entity_action_types/
	// Entity
	EntityActionType_AddVelocity		= 1,  // TODO
	EntityActionType_AddXP			= 2,  // TODO
	EntityActionType_ApplyEffect		= 3,  // TODO
	EntityActionType_AreaOfEffect		= 4,  // TODO
	EntityActionType_BlockActionAt		= 5,  // TODO
	EntityActionType_ChangeResource		= 6,  // TODO
	EntityActionType_ClearEffect		= 7,  // TODO
	EntityActionType_CraftingTable		= 8,  // TODO
	EntityActionType_Damage			= 9,  // TODO
	EntityActionType_Dismount		= 10, // TODO
	EntityActionType_EmitGameEvent		= 11, // TODO
	EntityActionType_EnderChest		= 12, // TODO
	EntityActionType_EquippedItemAction	= 13, // TODO
	EntityActionType_ExecuteCommand		= 14, // TODO
	EntityActionType_Exhaust		= 15, // TODO
	EntityActionType_Explode		= 16, // TODO
	EntityActionType_Extinguish		= 17, // TODO
	EntityActionType_Feed			= 18, // TODO
	EntityActionType_GainAir		= 19, // TODO
	EntityActionType_Give			= 20, // TODO
	EntityActionType_GrantPower		= 21, // TODO
	EntityActionType_Heal			= 22, // TODO
	EntityActionType_PassengerAction	= 23, // TODO
	EntityActionType_PlaySound		= 24, // TODO
	EntityActionType_Raycast		= 25, // TODO
	EntityActionType_RevokePower		= 26, // TODO
	EntityActionType_RidingAction		= 27, // TODO
	EntityActionType_SetFallDistance	= 28, // TODO
	EntityActionType_SetOnFire		= 29, // TODO
	EntityActionType_SpawnEffectCloud	= 30, // TODO
	EntityActionType_SpawnEntity		= 31, // TODO
	EntityActionType_SpawnParticles		= 32, // TODO
	EntityActionType_SwingHand		= 33, // TODO
	EntityActionType_Toggle			= 34, // TODO
	EntityActionType_TriggerCooldown	= 35  // TODO
};

enum ItemActionType {
	ItemActionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/item_action_types/
	// Item
	ItemActionType_Consume			= 1, // TODO
	ItemActionType_Damage			= 2, // TODO
	ItemActionType_Modify			= 3  // TODO
};

enum MetaActionType {
	MetaActionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/meta_action_types/
	// Meta
	MetaActionType_And			= 1, // TODO
	MetaActionType_Chance			= 2, // TODO
	MetaActionType_Choice			= 3, // TODO
	MetaActionType_Delay			= 4, // TODO
	MetaActionType_IfElseList		= 5, // TODO
	MetaActionType_IfElse			= 6, // TODO
	MetaActionType_Nothing			= 7  // TODO
};

enum BiEntityConditionType {
	BiEntityConditionType_None		= 0,
	// https://origins.readthedocs.io/en/latest/types/bientity_condition_types/
	// Bi-entity
	BiEntityConditionType_AttackTarget	= 1,   // TODO
	BiEntityConditionType_Attacker		= 2,   // TODO
	BiEntityConditionType_CanSee		= 3,   // TODO
	BiEntityConditionType_Distance		= 4,   // TODO
	BiEntityConditionType_Owner		= 5,   // TODO
	BiEntityConditionType_RelativeRotation	= 6,   // TODO
	BiEntityConditionType_RidingRecursive	= 7,   // TODO
	BiEntityConditionType_RidingRoot	= 8,   // TODO
	// Meta
	BiEntityConditionType_ActorCondition	= 10,  // TODO
	BiEntityConditionType_Both		= 11,  // TODO
	BiEntityConditionType_Either		= 12,  // TODO
	BiEntityConditionType_Invert		= 13,  // TODO
	BiEntityConditionType_TargetCondition	= 14,  // TODO
	BiEntityConditionType_Undirected	= 15,  // TODO
};

enum BiomeConditionType {
	BiomeConditionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/biome_condition_types/
	// Biome
	BiomeConditionType_Category		= 1,  // TODO
	BiomeConditionType_HighHumidity		= 2,  // TODO
	BiomeConditionType_Precipitation	= 3,  // TODO
	BiomeConditionType_Temperature		= 4   // TODO
};

enum BlockConditionType {
	BlockConditionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/block_condition_types/
	// Block
	BlockConditionType_Adjacent		= 1,  // TODO
	BlockConditionType_Attachable		= 2,  // TODO
	BlockConditionType_BlastResistance	= 3,  // TODO
	BlockConditionType_BlockState		= 4,  // TODO
	BlockConditionType_Block		= 5,  // TODO
	BlockConditionType_DistanceFromCoordinates=6, // TODO
	BlockConditionType_ExposedToSky		= 7,  // TODO
	BlockConditionType_Fluid		= 8,  // TODO
	BlockConditionType_Hardness		= 9,  // TODO
	BlockConditionType_Height		= 10, // TODO
	BlockConditionType_InTag		= 11, // TODO
	BlockConditionType_LightBlocking	= 12, // TODO
	BlockConditionType_LightLevel		= 13, // TODO
	BlockConditionType_Material		= 14, // TODO
	BlockConditionType_MovementBlocking	= 15, // TODO
	BlockConditionType_NBT			= 16, // TODO
	BlockConditionType_Replacable		= 17, // TODO
	BlockConditionType_Slipperiness		= 18, // TODO
	BlockConditionType_Waterloggable	= 19, // TODO
	// Meta
	BlockConditionType_Offset		= 20  // TODO
};

enum DamageConditionType {
	DamageConditionType_None		= 0,
	// https://origins.readthedocs.io/en/latest/types/damage_condition_types/
	// Damage
	DamageConditionType_Amount		= 1, // TODO
	DamageConditionType_Attacker		= 2, // TODO
	DamageConditionType_Fire		= 3, // TODO
	DamageConditionType_Name		= 4, // TODO
	DamageConditionType_Projectile		= 5  // TODO
};

enum EntityConditionType {
	EntityConditionType_None		= 0,
	// https://origins.readthedocs.io/en/latest/types/entity_condition_types/
	// Entity
	EntityConditionType_Ability		= 1,  // TODO
	EntityConditionType_Advancement		= 2,  // TODO
	EntityConditionType_Air			= 3,  // TODO
	EntityConditionType_Attribute		= 4,  // TODO
	EntityConditionType_Biome		= 5,  // TODO
	EntityConditionType_BlockCollision	= 6,  // TODO
	EntityConditionType_BlockInRadius	= 7,  // TODO
	EntityConditionType_Brightness		= 8,  // TODO
	EntityConditionType_Climbing		= 9,  // TODO
	EntityConditionType_CollidedHorizontally= 10, // TODO
	EntityConditionType_Command		= 11, // TODO
	EntityConditionType_CreativeFlying	= 12, // TODO
	EntityConditionType_Daytime		= 13, // TODO
	EntityConditionType_Dimension		= 14, // TODO
	EntityConditionType_DistanceFromCoordinates=15,//TODO
	EntityConditionType_ElytraFlightPossible= 16, // TODO
	EntityConditionType_Enchantment		= 17, // TODO
	EntityConditionType_EntityGroup		= 18, // TODO
	EntityConditionType_EntityType		= 19, // TODO
	EntityConditionType_EquippedItem	= 20, // TODO
	EntityConditionType_Exists		= 21, // TODO
	EntityConditionType_ExposedToSky	= 22, // TODO
	EntityConditionType_ExposedToSun	= 23, // TODO
	EntityConditionType_FallDistance	= 24, // TODO
	EntityConditionType_FallFlying		= 25, // TODO
	EntityConditionType_FluidHeight		= 26, // TODO
	EntityConditionType_FoodLevel		= 27, // TODO
	EntityConditionType_Gamemode		= 28, // TODO
	EntityConditionType_Health		= 29, // TODO
	EntityConditionType_InBlockAnywhere	= 30, // TODO
	EntityConditionType_InBlock		= 31, // TODO
	EntityConditionType_InRain		= 32, // TODO
	EntityConditionType_InTag		= 33, // TODO
	EntityConditionType_Invisible		= 34, // TODO
	EntityConditionType_Living		= 35, // TODO
	EntityConditionType_Moving		= 36, // TODO
	EntityConditionType_NBT			= 37, // TODO
	EntityConditionType_OnBlock		= 38, // TODO
	EntityConditionType_OnFire		= 39, // TODO
	EntityConditionType_Origin		= 40, // TODO
	EntityConditionType_PassengerRecursive	= 41, // TODO
	EntityConditionType_Passenger		= 42, // TODO
	EntityConditionType_PowerActive		= 43, // TODO
	EntityConditionType_PowerType		= 44, // TODO
	EntityConditionType_Power		= 45, // TODO
	EntityConditionType_Predicate		= 46, // TODO
	EntityConditionType_Raycast		= 47, // TODO
	EntityConditionType_RelativeHealth	= 48, // TODO
	EntityConditionType_Resource		= 49, // TODO
	EntityConditionType_RidingRecursive	= 50, // TODO
	EntityConditionType_RidingRoot		= 51, // TODO
	EntityConditionType_Riding		= 52, // TODO
	EntityConditionType_SaturationLevel	= 53, // TODO
	EntityConditionType_Scoreboard		= 54, // TODO
	EntityConditionType_Sneaking		= 55, // TODO
	EntityConditionType_Sprinting		= 56, // TODO
	EntityConditionType_StatusEffect	= 57, // TODO
	EntityConditionType_SubmergedIn		= 58, // TODO
	EntityConditionType_Swimming		= 59, // TODO
	EntityConditionType_Tamed		= 60, // TODO
	EntityConditionType_TimeOfDay		= 61, // TODO
	EntityConditionType_UsingEffectiveTool	= 62, // TODO
	EntityConditionType_UsingItem		= 63, // TODO
	EntityConditionType_XPLevels		= 64, // TODO
	EntityConditionType_XPPoints		= 65  // TODO
};

enum FluidConditionType {
	FluidConditionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/fluid_condition_types/
	// Fluid
	FluidConditionType_Empty		= 1, // TODO
	FluidConditionType_InTag		= 2, // TODO
	FluidConditionType_Still		= 3  // TODO
};

enum ItemConditionType {
	ItemConditionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/item_condition_types/
	// Item
	ItemConditionType_Amount		= 1,  // TODO
	ItemConditionType_ArmorValue		= 2,  // TODO
	ItemConditionType_Empty			= 3,  // TODO
	ItemConditionType_Enchantment		= 4,  // TODO
	ItemConditionType_Fireproof		= 5,  // TODO
	ItemConditionType_Food			= 6,  // TODO
	ItemConditionType_HarvestLevel		= 7,  // TODO
	ItemConditionType_Ingredient		= 8,  // TODO
	ItemConditionType_Meat			= 9,  // TODO
	ItemConditionType_NBT			= 10, // TODO
	ItemConditionType_Smeltable		= 11  // TODO
};

enum MetaConditionType {
	MetaConditionType_None			= 0,
	// https://origins.readthedocs.io/en/latest/types/meta_condition_types/
	// Meta
	MetaConditionType_And			= 1, // TODO
	MetaConditionType_Constant		= 2, // TODO
	MetaConditionType_Not			= 3, // TODO
	MetaConditionType_Or			= 4  // TODO
};


#endif//ORIGINS_HPP_INCLUDED

