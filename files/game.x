/* 0xEBC0000 is 0x2000000 in IDA/Ghidra/Cemu. For any offset >= 0xEBC0000, subtract 0xCBC0000 to get its value in IDA/Ghidra/Cemu. */
/* 0x10502200 is 0x10000000 in IDA/Ghidra/Cemu. For any offset >= 0x10502200, subtract 0x502200 to get its value in IDA/Ghidra/Cemu. */

SECTIONS {

	/* Math */
	sinf = 0xf6bdd40;   // <-- If applicable, use sead::Mathf::sinIdx. (or sead::Mathf::sinCosIdx)
	cosf = 0xf6be528;   // <-- If applicable, use sead::Mathf::cosIdx. (or sead::Mathf::sinCosIdx)
	atan2f = 0xf6be670; // <-- If applicable, use sead::Mathf::atan2Idx.
	powf = 0xF6BDEA8;
	sqrtf = 0xF6BDCCC; // <-- Do not use this. Use sead::Mathf::sqrt. (and sead::Mathf::rsqrt in place of 1/sqrt)

	/* new/delete */
	__nw__FUi = 0xF5B1594;
	__nw__FUiPQ2_4sead4Heapi = 0xF5B1858;
	__nwa__FUi = 0xf5b1630;
	__nwa__FUiPQ2_4sead4Heapi = 0xF5B18DC;
	__dl__FPv = 0xF5B1748;
	__dla__FPv = 0xF5B17D0;

	/* GHS C++ FUNCTIONS */
	__pure_virtual_called = 0xF6BA554;
	__deleted_virtual_called = 0xf6ba5e8;
	__vec_new = 0xF6BA350;

	/* GHS C FUNCTIONS */
	_f_ftoll = 0xF6BEBFC;
	__gh_float_printf = 0xF6BABA8;
	__memzero = 0xF6BA55C;

	/* GFD */
	GFDGetVertexShaderCount = 0xF6B8C04;
	GFDGetVertexShaderHeaderSize = 0xF6B8D00;
	GFDGetVertexShaderProgramSize = 0xF6B8D30;
	GFDGetVertexShader = 0xF6B8E3C;
	GFDGetPixelShaderCount = 0xF6B8C10;
	GFDGetPixelShaderHeaderSize = 0xF6B8D10;
	GFDGetPixelShaderProgramSize = 0xF6B8D40;
	GFDGetPixelShader = 0xF6B8FC0;
	_GFDCheckHeaderVersions = 0xF6B8A18;
	_GFDCheckBlockHeaderMagicVersions = 0xF6B8ABC;
	_GFDRelocateBlock = 0xF6B8E04;

	/* MTX Library */
	ASM_MTXConcat = 0xF6B98A0;
	ASM_VECMag = 0xF6B96C4;
	ASM_MTXScale = 0xF6B9B64;
	ASM_VECCrossProduct = 0xF6B9660;

	/* agl::lyr::DrawMethod */
	__vtbl__Q3_3agl3lyr10DrawMethod = 0x106AA254;
	__dt__Q3_3agl3lyr10DrawMethodFv = 0xF5F760C;

	/* agl::lyr::Renderer */
	sInstance__Q3_3agl3lyr8Renderer = 0x106EAC2C;
	draw__Q3_3agl3lyr8RendererCFQ3_3agl3lyr11DisplayType = 0xF5FAB90;
	initLayer__4__Q3_3agl3lyr8RendererFPQ3_3agl3lyr5LayeriRCQ2_4sead23SafeStringBase__tm__2_cQ3_3agl3lyr11DisplayTypePQ2_4sead4Heap = 0xF5FAEEC;

	/* agl::lyr::Renderer::createLayer<T> */
	createLayer__tm__30_Q2_16CourseSelectTask7Layer2D__Q3_3agl3lyr8RendererFiRCQ2_4sead23SafeStringBase__tm__2_cQ3_3agl3lyr11DisplayTypePQ2_4sead4Heap_PZ1Z = 0xEDAF0F0;
	createLayer__tm__17_14RenderObjLayer__Q3_3agl3lyr8RendererFiRCQ2_4sead23SafeStringBase__tm__2_cQ3_3agl3lyr11DisplayTypePQ2_4sead4Heap_PZ1Z = 0xEDAF180;

	/* agl::lyr::Layer */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q3_3agl3lyr5LayerSFv = 0x106EBF20;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q3_3agl3lyr5LayerSFv = 0x106EC26C;
	pushBackDrawMethod__Q3_3agl3lyr5LayerFUiPQ3_3agl3lyr10DrawMethod = 0xF5F76B8;
	pushBackDrawMethod__Q3_3agl3lyr5LayerFPQ3_3agl3lyr10DrawMethod = 0xF5F7710;

	/* agl::TextureData */
	__ct__Q2_3agl11TextureDataFv = 0xF5E49A0;
	__dt__Q2_3agl11TextureDataFv = __deleted_virtual_called;
	invalidateGPUCache__Q2_3agl11TextureDataFv = 0xF5E4A64;

	/* agl::TextureDataInitializerGTX */
	initialize__Q2_3agl25TextureDataInitializerGTXSFPQ2_3agl11TextureDataPvUi = 0xF5E4F38;

	/* agl::TextureSampler */
	__ct__Q2_3agl14TextureSamplerFv = 0xF5E587C;
	__dt__Q2_3agl14TextureSamplerFv = 0xF5E5C60;
	applyTextureData___Q2_3agl14TextureSamplerFRCQ2_3agl11TextureData = 0xF5E5990;
	activate__Q2_3agl14TextureSamplerCFRCQ2_3agl15SamplerLocationi = 0xF5E5F18;

	/* nw::eft::EmitterSet */
	SetMtx__Q3_2nw3eft10EmitterSetFRCQ3_2nw4math5MTX34 = 0xF62AD00;

	/* nw::eft::Random */
	__LSG__a__L0__Init__Q3_2nw3eft6RandomFUi = 0x106EBE88;
	a__L0__Init__Q3_2nw3eft6RandomFUi = 0x106EDE7C;

	/* nw::eft::System */
	__vtbl__Q3_2nw3eft6System = 0x106B3C78;
	Initialize__Q3_2nw3eft6SystemFPQ3_2nw3eft4HeapRCQ3_2nw3eft6Config = 0xF636F94;
	CreateEmitterSetID__Q3_2nw3eft6SystemFPQ3_2nw3eft6HandleRCQ3_2nw4math5MTX34iUiUcT4 = 0xF63F57C;

	/* nw::math */
	F_PI__Q2_2nw4math = 0x106B82FC;
	I_HALF_ROUND_IDX__Q2_2nw4math = 0x106B8300;

	/* nw::math::internal */
	gSinCosTbl__Q3_2nw4math8internal = 0x106B830C;

	/* nw::math::MTX34 */
	__LSG__identity__L0__Identity__Q3_2nw4math5MTX34SFv = 0x106EBA08;
	identity__L0__Identity__Q3_2nw4math5MTX34SFv = 0x106EC9D8;

	/* nw::math::MTX44 */
	__LSG__identity__L0__Identity__Q3_2nw4math5MTX44SFv = 0x106EBA0C;
	identity__L0__Identity__Q3_2nw4math5MTX44SFv = 0x106EDED0;

	/* nw::math::VEC2 */
	__LSG__zero__L0__Zero__Q3_2nw4math4VEC2SFv = 0x106EB9EC;
	zero__L0__Zero__Q3_2nw4math4VEC2SFv = 0x106EDE74;

	/* nw::math::VEC3 */
	__LSG__zero__L0__Zero__Q3_2nw4math4VEC3SFv = 0x106EB9F0;
	zero__L0__Zero__Q3_2nw4math4VEC3SFv = 0x106ED104;

	/* sead::CalculateTask */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead13CalculateTaskSFv = 0x106EBC9C;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead13CalculateTaskSFv = 0x106EC964;
	__ct__Q2_4sead13CalculateTaskFRCQ2_4sead16TaskConstructArgPCc = 0xF5BC508;
	__dt__Q2_4sead13CalculateTaskFv = 0xF5BC2F0;
	pauseCalc__Q2_4sead13CalculateTaskFb = 0xF5BC444;
	pauseDraw__Q2_4sead13CalculateTaskFb = 0xF5BC85C;
	pauseCalcRec__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
	pauseDrawRec__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
	pauseCalcChild__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
	pauseDrawChild__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
	attachCalcImpl__Q2_4sead13CalculateTaskFv = 0xF5BC384;
	attachDrawImpl__Q2_4sead13CalculateTaskFv = 0xF5BC854;
	detachCalcImpl__Q2_4sead13CalculateTaskFv = 0xF5BC43C;
	detachDrawImpl__Q2_4sead13CalculateTaskFv = 0xF5BC858;
	getCorrespondingMethodTreeMgrTypeInfo__Q2_4sead13CalculateTaskCFv = __deleted_virtual_called;
	getMethodTreeNode__Q2_4sead13CalculateTaskFi = 0xF5BC4F0;

	/* sead::Camera */
	__vtbl__Q2_4sead6Camera = 0x10692A24;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead6CameraSFv = 0x106EBD88;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead6CameraSFv = 0x106EDE10;

	/* sead::Color4f */
	cWhite__Q2_4sead7Color4f = 0x10AEC2A0;

	/* sead::DirectResource */
	__vtbl__Q2_4sead14DirectResource = 0x106A5C78;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14DirectResourceSFv = 0x106EBDB8;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14DirectResourceSFv = 0x106EC118;

	/* sead::Endian */
	cHostEndian__Q2_4sead6Endian = 0x10AECC78;
	cConvFuncTable__Q2_4sead6Endian = 0x10694BA8;

	/* sead::FileDevice */
	__CPR122__tryOpen__Q2_4sead10FileDeviceFPQ2_J12J10FileHandleRCQ2_J12J23SafeStringBase__tm__2_cQ3_J12JJ17J12FileOpenFlagUi = 0xF5B7804;
	tryClose__Q2_4sead10FileDeviceFPQ2_4sead10FileHandle = 0xF5B78C0;

	/* sead::FileDeviceMgr */
	sInstance__Q2_4sead13FileDeviceMgr = 0x106EA118;
	tryOpen__Q2_4sead13FileDeviceMgrFPQ2_4sead10FileHandleRCQ2_4sead23SafeStringBase__tm__2_cQ3_4sead10FileDevice12FileOpenFlagUi = 0xF5B8B0C;
	tryLoad__Q2_4sead13FileDeviceMgrFRQ3_4sead10FileDevice7LoadArg = 0xF5B8BBC;

	/* sead::FileHandle */
	read__Q2_4sead10FileHandleFPUcUi = 0xF5B81D0;
	tryRead__Q2_4sead10FileHandleFPUiPUcUi = 0xF5B8230;
	getFileSize__Q2_4sead10FileHandleFv = 0xF5B8368;

	/* sead::FrameBuffer */
	bind__Q2_4sead11FrameBufferCFv = 0xF5C58F0;

	/* sead::GraphicsContext */
	__ct__Q2_4sead15GraphicsContextFv = 0xF5C7BBC;
	apply__Q2_4sead15GraphicsContextCFv = 0xF5C7CB0;

	/* sead::Heap */
	/* __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead4HeapSFv */
	/* typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead4HeapSFv */

	/* sead::HeapMgr */
	sInstancePtr__Q2_4sead7HeapMgr = 0x106EA240;
	getCurrentHeap__Q2_4sead7HeapMgrCFv = 0xF5CD554;

	/* sead::IDisposer */
	__vtbl__Q2_4sead9IDisposer = 0x106931A8;
	__ct__Q2_4sead9IDisposerFv = 0xF5CA2FC;
	__dt__Q2_4sead9IDisposerFv = 0xf5ca384;

	/* sead::LookAtCamera */
	__vtbl__Q2_4sead12LookAtCamera = 0x10692A4C;
	__dt__Q2_4sead12LookAtCameraFv = 0xF5C4B94;
	doUpdateMatrix__Q2_4sead12LookAtCameraCFPQ2_4sead17Matrix34__tm__2_f = 0xF5C4BE8;

	/* sead::MathCalcCommon<f32> */
	cSinCosTbl__S__Q2_4sead23MathCalcCommon__tm__2_f = 0x10693738;
	atanIdx___S__Q2_4sead23MathCalcCommon__tm__2_fSFZ1Z_Ui = 0xF5CE124;

	/* sead::Matrix34<f32> */
	ident__S__Q2_4sead17Matrix34__tm__2_f = 0x10AEC458;

	/* sead::Matrix34CalcCommon<f32> */
	__CPR161__makeRTIdx__Q2_4sead27Matrix34CalcCommon__tm__2_fSFRQ3_J14J19Policies__tm__4_Z1Z9Mtx34BaseRCQ2_J14J17Vector3__tm__3_UiRCQ3_J14JJ59J8Vec3Base_v = 0xebfc1c8;
	__CPR128__makeQ__Q2_4sead27Matrix34CalcCommon__tm__2_fSFRQ3_J10J19Policies__tm__4_Z1Z9Mtx34BaseRCQ3_J10JJ55J8QuatBase_v = 0xEC1A79C;
	__CPR131__makeST__Q2_4sead27Matrix34CalcCommon__tm__2_fSFRQ3_J11J19Policies__tm__4_Z1Z9Mtx34BaseRCQ3_J11JJ56J8Vec3BaseT2_v = 0xEDE2A88;
	__CPR133__makeSRT__Q2_4sead27Matrix34CalcCommon__tm__2_fSFRQ3_J12J19Policies__tm__4_Z1Z9Mtx34BaseRCQ3_J12JJ57J8Vec3BaseN22_v = 0xF0C8424;
	__CPR137__setTranslation__Q2_4sead27Matrix34CalcCommon__tm__2_fSFRQ3_J19J19Policies__tm__4_Z1Z9Mtx34BaseRCQ3_J19JJ64J8Vec3Base_v = 0xEC06174;
	__CPR131__setBase__Q2_4sead27Matrix34CalcCommon__tm__2_fSFRQ3_J12J19Policies__tm__4_Z1Z9Mtx34BaseiRCQ3_J12JJ57J8Vec3Base_v = 0xEC06150;

	/* sead::MethodTreeNode */
	/* __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14MethodTreeNodeSFv */
	/* typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14MethodTreeNodeSFv */

	/* sead::PrimitiveRenderer */
	sInstance__Q2_4sead17PrimitiveRenderer = 0x106EA210;
	setCamera__Q2_4sead17PrimitiveRendererFRCQ2_4sead6Camera = 0xF5C83D0;
	setProjection__Q2_4sead17PrimitiveRendererFRCQ2_4sead10Projection = 0xF5C83E4;
	setModelMatrix__Q2_4sead17PrimitiveRendererFRCQ2_4sead17Matrix34__tm__2_f = 0xF5C83F8;
	begin__Q2_4sead17PrimitiveRendererFv = 0xF5C8408;
	end__Q2_4sead17PrimitiveRendererFv = 0xF5C841C;
	__CPR75__drawQuad__Q2_4sead17PrimitiveRendererFRCQ3_J13JJ18J7QuadArg = 0xF5C8430;

	/* sead::PrimitiveRenderer::QuadArg */
	setColor__Q3_4sead17PrimitiveRenderer7QuadArgFRCQ2_4sead7Color4fT1 = 0xF5C8628;

	/* sead::Projection */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead10ProjectionSFv = 0x106EBD74;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead10ProjectionSFv = 0x106ECA08;
	getDeviceProjectionMatrix__Q2_4sead10ProjectionCFv = 0xF5C5A9C;

	/* sead::PerspectiveProjection */
	__ct__Q2_4sead21PerspectiveProjectionFv = 0xF5C6108;
	__dt__Q2_4sead21PerspectiveProjectionFv = 0xF5C6298;
	set__Q2_4sead21PerspectiveProjectionFfN31 = 0xF5C62EC;

	/* sead::Quat<f32> */
	unit__S__Q2_4sead13Quat__tm__2_f = 0x10AEC798;

	/* sead::QuatCalcCommon<f32> */
	__CPR138__makeVectorRotation__Q2_4sead23QuatCalcCommon__tm__2_fSFRQ3_J23J19Policies__tm__4_Z1Z8QuatBaseRCQ3_J23JJ64J8Vec3BaseT2_b = 0xEC1A660;

	/* sead::Resource */
	__vtbl__Q2_4sead8Resource = 0x106A5C50;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead8ResourceSFv = 0x106EBDB4;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead8ResourceSFv = 0x106EC114;

	/* sead::ResourceMgr */
	sInstance__Q2_4sead11ResourceMgr = 0x106EA274;
	unregisterDecompressor__Q2_4sead11ResourceMgrFPQ2_4sead12Decompressor = 0xF5D3FA8;

	/* sead::SafeStringBase<char> */
	cNullChar__S__Q2_4sead23SafeStringBase__tm__2_c = 0x10502244;

	/* sead::SZSDecompressor */
	__vtbl__Q2_4sead15SZSDecompressor = 0x106A5F68;
	__vtbl__42Q2_4sead9IDisposer__Q2_4sead12Decompressor__Q2_4sead15SZSDecompressor = 0x106A5F80;
	__dt__Q2_4sead15SZSDecompressorFv = 0xF5D5FA8;
	getDecompSize__Q2_4sead15SZSDecompressorSFPCv = 0xF5D54CC;
	getDecompAlignment__Q2_4sead15SZSDecompressorSFPCv = 0xF5D5AA0;
	decomp__Q2_4sead15SZSDecompressorSFPvUiPCvT2 = 0xF5D5654;
	__CPR87__streamDecomp__Q2_4sead15SZSDecompressorSFPQ3_J17JJ22J13DecompContextPCvUi = 0xF5D57FC;

	/* sead::SZSDecompressor::DecompContext */
	__ct__Q3_4sead15SZSDecompressor13DecompContextFPv = 0xF5D5AF4;

	/* sead::TaskBase */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead8TaskBaseSFv = 0x106EBC98;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead8TaskBaseSFv = 0x106EC968;
	enterCommon__Q2_4sead8TaskBaseFv = 0xF5BF818;
	onEvent__Q2_4sead8TaskBaseFRCQ2_4sead9TaskEvent = 0xF5BFF78;
	onDestroy__Q2_4sead8TaskBaseFv = __deleted_virtual_called;
	doneDestroy__Q2_4sead8TaskBaseFv = __deleted_virtual_called;

	/* sead::TaskMgr */
	destroyTaskSync__Q2_4sead7TaskMgrFPQ2_4sead8TaskBase = 0xF5C0D98;

	/* sead::UnitHeap */
	/* __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead8UnitHeapSFv */
	/* typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead8UnitHeapSFv */

	/* sead::Vector3<f32> */
	zero__S__Q2_4sead16Vector3__tm__2_f = 0x10AEC960;
	ones__S__Q2_4sead16Vector3__tm__2_f = 0x10AEC990;

	/* sead::Vector3CalcCommon<f32> */
	normalize__Q2_4sead26Vector3CalcCommon__tm__2_fSFRQ3_4sead19Policies__tm__4_Z1Z8Vec3Base_Z1Z = 0xEC1A5F4;

	/* sead::Vector4<f32> */
	zero__S__Q2_4sead16Vector4__tm__2_f = 0x10AEC99C;

	/* sead::Viewport */
	__ct__Q2_4sead8ViewportFRCQ2_4sead18LogicalFrameBuffer = 0xF5C74C8;
	apply__Q2_4sead8ViewportCFRCQ2_4sead18LogicalFrameBuffer = 0xF5C783C;

	/* Profile */
	profilesOriginal__7Profile = 0x106EFADC;
	prioritiesOriginal__7Profile = 0x10503B40;
	hasResourcesOriginal__7Profile = 0x10504264;
	resourceCountOriginal__7Profile = 0x105045F8;
	resourceListsOriginal__7Profile = 0x106C541C;

	/* ActorInfo */
	Default__9ActorInfo = 0x10503AF4;

	/* ActorMgr */
	instance__8ActorMgr = 0x106c52c8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0xebc9a58;

	/* Base */
	__vtbl__4Base = 0x105028c0;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__4BaseSFv = 0x106EBEC4;
	typeInfo__L0__getRuntimeTypeInfoStatic__4BaseSFv = 0x106EBEC8;
	beforeCreate__4BaseFv = 0xebc2f7c;
	onExecute__4BaseFv = 0xebc2f8c;
	finalExecute__4BaseFv = 0xebc2f94;
	onDraw__4BaseFv = 0xebc2fa0;
	afterDraw__4BaseFUi = 0xebc2f38;
	beforeDelete__4BaseFv = 0xebc2fa8;
	onDelete__4BaseFv = 0xebc2fb0;
	afterDelete__4BaseFUi = 0xebc2f3c;

	/* Actor */
	__vtbl__5Actor = 0x10502468;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x106EBEBC;
	typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x106EBEC0;
	__ct__5ActorFPC14ActorBuildInfo = 0xebc0ac8;
	directionToPlayerH__5ActorFRC4Vec3 = 0xebc05ec;
	directionToActorH__5ActorFRC5Actor = 0xEBCC800;
	distanceToPlayer__5ActorFR4Vec2 = 0xebc05a4;
	deleteActorWhenOutOfView__5ActorFUi = 0xEBC07A0;
	actorAcCallback0__5ActorFP14ActiveColliderPQ2_4sead16Vector2__tm__2_f = 0xED5E7E8;
	actorAcCallback2__5ActorFP14ActiveColliderPQ2_4sead16Vector2__tm__2_f = 0xED5E8A4;
	actorCbCallback0__5ActorFP12ColliderBasePQ2_4sead16Vector2__tm__2_f = 0xED5E8B8;
	checkDerivedRuntimeTypeInfo__5ActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xebc2a38;
	getRuntimeTypeInfo__5ActorCFv = __deleted_virtual_called;
	__dt__5ActorFv = 0xebc0f18;
	afterCreate__5ActorFUi = 0xebc0fb8;
	beforeExecute__5ActorFv = 0xebc0fe8;
	afterExecute__5ActorFUi = 0xebc10bc;
	beforeDraw__5ActorFv = 0xebc11a0;
	removeActiveColliders__5ActorFv = 0xebc02cc;
	addActiveColliders__5ActorFv = 0xebc0328;
	killAtGoal__5ActorFv = 0xebc2ad8;
	splashWater__5ActorFPQ2_4sead16Vector3__tm__2_f = 0xebc2adc;
	splashLava__5ActorFPQ2_4sead16Vector3__tm__2_f = 0xebc2ae0;
	splashLavaWave__5ActorFPQ2_4sead16Vector3__tm__2_f = 0xebc0960;
	splashPoison__5ActorFPQ2_4sead16Vector3__tm__2_f = 0xebc2ae4;
	isOffScreen__5ActorFv = 0xebc1254;

	/* StageActor */
	__vtbl__10StageActor = 0x10502a4c;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBED4;
	typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBED8;
	handleGravity__10StageActorFv = 0xEBC39AC;
	handleSpeed__10StageActorFv = 0xEBC3AE4;
	afterCreate__10StageActorFUi = 0xebc354c;
	beforeExecute__10StageActorFv = 0xebc35fc;
	afterExecute__10StageActorFUi = 0xebc36d8;
	onDelete__10StageActorFv = 0xebc3724;
	vf114__10StageActorFv = __deleted_virtual_called;
	vf134__10StageActorFv = __deleted_virtual_called;
	vf13C__10StageActorFv = 0xebc4008;
	vf144__10StageActorFb = 0xebc375c;
	vf14C__10StageActorFP5Actor = 0xebc3760;

	/* ActorState */
	__vtbl__10ActorState = 0x105030c8;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10ActorStateSFv = 0x106EBEDC;
	typeInfo__L0__getRuntimeTypeInfoStatic__10ActorStateSFv = 0x106EBEE0;

	/* ActorMultiState */
	__vtbl__15ActorMultiState = 0x10503248;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__15ActorMultiStateSFv = 0x106EBEE4;
	typeInfo__L0__getRuntimeTypeInfoStatic__15ActorMultiStateSFv = 0x106EBEE8;
	__ct__15ActorMultiStateFPC14ActorBuildInfo = 0xebcaa8c;
	checkDerivedRuntimeTypeInfo__15ActorMultiStateCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xebcaf94;

	/* BlockCoinBase */
	__vtbl__13BlockCoinBase = 0x10603c80;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__13BlockCoinBaseSFv = 0x106EBEA4;
	typeInfo__L0__getRuntimeTypeInfoStatic__13BlockCoinBaseSFv = 0x106EBEA8;
	StateID_BlockCoinState3__13BlockCoinBase = 0x10722764;
	StateID_BumpUp2__13BlockCoinBase = 0x1072271C;
	checkDerivedRuntimeTypeInfo__13BlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xf2c8dc0;
	vf18C__13BlockCoinBaseFv = 0xf2c8efc;
	vf194__13BlockCoinBaseFv = 0xf2c8f00;
	setBelowSensor__13BlockCoinBaseFv = 0xf2c8f04;
	vf1A4__13BlockCoinBaseFv = 0xf2c8f08;
	spawnItemUp__13BlockCoinBaseFv = 0xf2c8f0c;
	vf1B4__13BlockCoinBaseFv = 0xf2c8f10;
	vf1BC__13BlockCoinBaseFv = 0xf2c8f14;
	spawnItemDown__13BlockCoinBaseFv = 0xf2c8f18;
	vf1CC__13BlockCoinBaseFv = 0xf2c8f1c;
	vf1D4__13BlockCoinBaseFb = 0xf2c4868;
	vf1DC__13BlockCoinBaseFv = 0xf2c8f20;
	spawnCoinShower__13BlockCoinBaseFv = 0xf2c48e4;
	vf1EC__13BlockCoinBaseFv = 0xf2c8f28;
	beginState_BumpUp__13BlockCoinBaseFv = 0xf2c7cb4;
	executeState_BumpUp__13BlockCoinBaseFv = 0xf2c7cf0;
	endState_BumpUp__13BlockCoinBaseFv = 0xf2c8f2c;
	beginState_BlockCoinState1__13BlockCoinBaseFv = 0xf2c7d94;
	executeState_BlockCoinState1__13BlockCoinBaseFv = 0xf2c7da0;
	endState_BlockCoinState1__13BlockCoinBaseFv = 0xf2c8f30;
	beginState_BumpDown__13BlockCoinBaseFv = 0xf2c7db8;
	executeState_BumpDown__13BlockCoinBaseFv = 0xf2c7dfc;
	endState_BumpDown__13BlockCoinBaseFv = 0xf2c8f34;
	beginState_BlockCoinState2__13BlockCoinBaseFv = 0xf2c7e9c;
	executeState_BlockCoinState2__13BlockCoinBaseFv = 0xf2c7ea8;
	endState_BlockCoinState2__13BlockCoinBaseFv = 0xf2c8f38;
	beginState_BumpUp2__13BlockCoinBaseFv = 0xf2c7ed0;
	executeState_BumpUp2__13BlockCoinBaseFv = 0xf2c7f58;
	endState_BumpUp2__13BlockCoinBaseFv = 0xf2c8f3c;
	beginState_BumpDown2__13BlockCoinBaseFv = 0xf2c812c;
	executeState_BumpDown2__13BlockCoinBaseFv = 0xf2c8198;
	endState_BumpDown2__13BlockCoinBaseFv = 0xf2c8f40;
	beginState_BlockCoinState3__13BlockCoinBaseFv = 0xf2c828c;
	executeState_BlockCoinState3__13BlockCoinBaseFv = 0xf2c8298;
	endState_BlockCoinState3__13BlockCoinBaseFv = 0xf2c8f44;
	spawnPortableSpring__13BlockCoinBaseFv = 0xf2c6430;
	spawnVine__13BlockCoinBaseFv = 0xf2c62a8;
	spawnYoshiEgg__13BlockCoinBaseFb = 0xf2c6ba4;
	spawnPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0xf2c6d1c;
	spawnMultiPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0xf2c6ff4;

	/* MovementBlockCoinBase */
	__vtbl__21MovementBlockCoinBase = 0x106097ac;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__21MovementBlockCoinBaseSFv = 0x106EBEEC;
	typeInfo__L0__getRuntimeTypeInfoStatic__21MovementBlockCoinBaseSFv = 0x106EBEF0;
	checkDerivedRuntimeTypeInfo__21MovementBlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xf2e7a08;
	spawnItemUp__21MovementBlockCoinBaseFv = 0xf2e6610;
	spawnItemDown__21MovementBlockCoinBaseFv = 0xf2e6634;
	vf1DC__21MovementBlockCoinBaseFv = 0xf2e6644;
	vf1EC__13BlockCoinBaseFv = 0xf2e7980;
	vf29C__21MovementBlockCoinBaseFv = 0xf2e7984;
	setTileFlag__21MovementBlockCoinBaseFv = 0xf2e65bc;
	vf2AC__21MovementBlockCoinBaseFv = 0xf2e7988;
	vf2B4__21MovementBlockCoinBaseFv = 0xf2e7990;
	vf2BC__21MovementBlockCoinBaseFv = 0xf2e7994;
	vf2C4__21MovementBlockCoinBaseFv = 0xf2e7998;
	vf2CC__21MovementBlockCoinBaseFv = 0xf2e6654;
	registerColliderActiveInfo__21MovementBlockCoinBaseFv = 0xF2E6760;

	/* BlockBase */
	StateID_Wait__9BlockBase = 0x10720ae0;
	StateID_Used__9BlockBase = 0x10720b04;
	activeTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C4ECC;
	activeBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C5528;
	activeSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C5EFC;
	usedTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xf2c50f0;
	usedBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xf2c595c;
	usedSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xf2c60c0;
	init__9BlockBaseFbT1 = 0xf25f6c8;
	initMover__9BlockBaseFv = 0xF25FB30;
	__vtbl__9BlockBase = 0x105e8b60;
	__ct__9BlockBaseFPC14ActorBuildInfo = 0xf25e614;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x106EBEF4;
	typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x106EBEF8;
	checkDerivedRuntimeTypeInfo__9BlockBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xf260460;
	getRuntimeTypeInfo__9BlockBaseCFv = __deleted_virtual_called;
	onExecute__9BlockBaseFv = 0xf25e6c4;
	onDraw__9BlockBaseFv = 0xf25e77c;
	setBelowSensor__9BlockBaseFv = 0xf25f400;
	spawnItemUp__9BlockBaseFv = 0xf25ebc0;
	spawnItemDown__9BlockBaseFv = 0xf25ebc4;
	vf1CC__9BlockBaseFv = 0xf25ec04;
	vf1EC__9BlockBaseFv = 0xF25F674;
	vf2C4__9BlockBaseFv = 0xf25f410;
	isActive__9BlockBaseFv = 0xf25ec1c;
	vf2DC__9BlockBaseFv = 0xf260404;
	getContent__9BlockBaseFv = 0xf260408;
	vf2EC__9BlockBaseFv = 0xf25efe4;
	vf2F4__9BlockBaseFPv = 0xf260418;
	execute__9BlockBaseFv = 0xf25f078;
	destroy__9BlockBaseFv = 0xf25f25c;
	destroy2__9BlockBaseFv = 0xf25f33c;
	vf314__9BlockBaseFv = 0xf260434;
	vf31C__9BlockBaseFv = 0xf260438;
	vf324__9BlockBaseFv = 0xf26043c;
	vf32C__9BlockBaseFv = 0xf260440;
	beginState_Wait__9BlockBaseFv = 0xf26061c;
	executeState_Wait__9BlockBaseFv = 0xf260068;
	endState_Wait__9BlockBaseFv = 0xf260620;
	beginState_Used__9BlockBaseFv = 0xf260624;
	executeState_Used__9BlockBaseFv = 0xf260074;
	endState_Used__9BlockBaseFv = 0xf260628;

	/* ActiveCollider */
	__ct__14ActiveColliderFv = 0xED5A960;
	__dt__14ActiveColliderFv = 0xED5AB90;
	__CPR59__init__14ActiveColliderFP5ActorPCQ2_J6J4InfoPPv = 0xed5af1c;
	Default__Q2_14ActiveCollider4Info = 0x10543DC0;

	/* ActiveColliderMgr */
	instance__17ActiveColliderMgr = 0x106CB7D8;

	/* ColliderBase */
	setType__12ColliderBaseFQ2_12ColliderBase5Types = 0xED65A70;
	__CPR62__setSurfaceType__12ColliderBaseFQ2_J16J12SurfaceTypes = 0xED65AD0;

	/* ColliderBase::Node */
	__ct__Q2_12ColliderBase4NodeFv = 0xED61ACC;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x106EBF2C;
	typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x106EC1A4;

	/* ShapedCollider */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x106EBF30;
	typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x106EC1B4;
	__ct__14ShapedColliderFiPQ2_4sead16Vector2__tm__2_fPQ2_12ColliderBase4NodeT3 = 0xED67904;
	init__14ShapedColliderFP5ActorRCQ2_14ShapedCollider4Info = 0xed6d3bc;
	execute__14ShapedColliderFv = 0xED6871C;
	__dt__14ShapedColliderFv = 0xED67A04;
	setRect__14ShapedColliderFP4Vec2T1 = 0xed6d25c;

	/* RectCollider */
	__vtbl__12RectCollider = 0x105FDA20;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12RectColliderSFv = 0x106EBF38;
	typeInfo__L0__getRuntimeTypeInfoStatic__12RectColliderSFv = 0x106EC1BC;

	/* SolidOnTopCollider */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x106EBF48;
	typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x106EC1A8;
	__ct__18SolidOnTopColliderFv = 0xED61D38;
	__CPR79__init__18SolidOnTopColliderFP5ActorRCQ2_J6J4InfoiPQ2_4sead4Heap = 0xED62378;
	execute__18SolidOnTopColliderFv = 0xED62E0C;
	__dt__18SolidOnTopColliderFv = 0xED61F18;

	/* CircularCollider */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__16CircularColliderSFv = 0x106EC188;
	typeInfo__L0__getRuntimeTypeInfoStatic__16CircularColliderSFv = 0x106EC598;

	/* ColliderMgr */
	sInstance__11ColliderMgr = 0x106CB560;
	add__11ColliderMgrFP12ColliderBase = 0xED5269C;
	remove__11ColliderMgrFP12ColliderBase = 0xED5282C;

	/* StateBase */
	currentId__9StateBase = 0x106ec104;
	NullState__9StateBase = 0x1072F590;

	/* StateMgr */
	execute__8StateMgrFv = 0xf584a80;
	changeState__8StateMgrFP9StateBase = 0xF584AF0;

	/* CollisionMgr */
	/* __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12CollisionMgrSFv */
	/* typeInfo__L0__getRuntimeTypeInfoStatic__12CollisionMgrSFv */
	__dt__12CollisionMgrFv = 0xED4ADFC;
	init__12CollisionMgrFP5ActorPCQ2_12CollisionMgr6SensorN22 = 0xED4AF6C;
	setSensor__12CollisionMgrFPCQ2_12CollisionMgr6SensorUi = 0xED4AEFC;
	getSensor__12CollisionMgrCFUi = 0xED4CE74;
	process__12CollisionMgrFv = 0xED4D954;

	/* ActorCollisionMgr */
	/* __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__17ActorCollisionMgrSFv */
	/* typeInfo__L0__getRuntimeTypeInfoStatic__17ActorCollisionMgrSFv */

	/* EventMgr */
	sInstance__8EventMgr = 0x106dd26c;

	/* MusicPlayer */
	shouldHurryUp__11MusicPlayerFv = 0xF5783D8;

	/* ResArchive */
	getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0xf0ae440;

	/* ResArchiveMgr */
	instance__13ResArchiveMgr = 0x106d4f50;
	get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0xf0b60ec;

	/* Model */
	__vtbl__5Model = 0x105bf130;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__5ModelSFv = 0x106EC178;
	typeInfo__L0__getRuntimeTypeInfoStatic__5ModelSFv = 0x106EC1A0;

	/* ModelWrapper */
	__ct__12ModelWrapperFP5ModelUiN42 = 0xf094798;
	setup__12ModelWrapperFP10ResArchivePvPQ2_4sead4Heap = 0xf0949a0;
	updateAnimations__12ModelWrapperFv = 0xf094d20;
	updateModel__12ModelWrapperFv = 0xf094e84;

	/* DrawMgr */
	instance__7DrawMgr = 0x106d4f88;
	drawModel__7DrawMgrFP5Model = 0xf0bab58;
	drawModel__7DrawMgrFP12ModelWrapper = 0xf0bac98;
	drawTile__7DrawMgrFUsRCQ2_4sead16Vector3__tm__2_fRCUiT2 = 0xf0bad28;
	setTargetLayer__7DrawMgrFP8ObjLayerUi = 0xF0BAA50;
	resetTargetLayer__7DrawMgrFv = 0xF0BAB4C;

	/* MovementHandler */
	__ct__15MovementHandlerFv = 0xF409C40;
	link__15MovementHandlerFRCQ2_4sead16Vector3__tm__2_fUiUc = 0xF40B6F4;
	getMaskForMovementType__15MovementHandlerFUi = 0xF40A37C;
	execute__15MovementHandlerFv = 0xF40B8C4;

	/* SoundSystemBase */
	getAudioFx__15SoundSystemBaseFv = 0xF571AA4;

	/* SoundSystem */
	instance__11SoundSystem = 0x106E9E84;

	/* AudioFx */
	getReverbHiParam__7AudioFxFv = 0xF572FD8;
	getDelayParam__7AudioFxFv = 0xF572FE0;

	/* Level */
	sInstance__5Level = 0x106dd248;
	getArea__5LevelFUi = 0xf25a2dc;

	/* Level::Area */
	getSprite__Q2_5Level4AreaFUiPv = 0xF259C08;
	getLocation__Q2_5Level4AreaFPQ2_4sead18BoundBox2__tm__2_fUc = 0xf25a020;
	getPath__Q2_5Level4AreaFUc = 0xf25a0a8;
	getPathNodes__Q2_5Level4AreaFUi = 0xf25a0f4;

	/* LevelInfo */
	sInstance__9LevelInfo = 0x106D3AEC;

	/* TileMgr */
	getTilePtrCurrentArea__7TileMgrSFUsT1UcPUi = 0xF245000;

	/* PlayerMgr */
	sInstance__9PlayerMgr = 0x106E8B94;

	/* AreaTask */
	drawLayer3D__8AreaTaskFRCQ3_3agl3lyr10RenderInfo = 0xF0784A8;

	/* TwoWayPlatform */
	cbCallback4__14TwoWayPlatformSFP5Actor = 0xF3FFBAC;
	cbCallback5__14TwoWayPlatformSFP5Actor = 0xF3FFBE0;
	cbCallback6__14TwoWayPlatformSFP5ActorUiT2 = 0xF3FFC14;
	twoWayPlatformCbCallback2__14TwoWayPlatformFP12ColliderBasePQ2_4sead16Vector2__tm__2_f = 0xF40184C;

	/* PtclMgr */
	sInstance__7PtclMgr = 0x106CF5A8;
	getEmitterSetGroupID__7PtclMgrCFiUi = 0xEE6CE58;

	/* PlayerInput */
	isDownPressed__11PlayerInputCFv = 0xF4D6114;
	isDownHeld__11PlayerInputCFv = 0xF4D5F84;
	isOnlyDownHeld__11PlayerInputCFv = 0xF4D644C;
	isUpPressed__11PlayerInputCFv = 0xF4D6108;
	isUpHeld__11PlayerInputCFv = 0xF4D5F78;
	isRightHeld__11PlayerInputCFv = 0xF4D5F9C;
	isLeftHeld__11PlayerInputCFv = 0xF4D5F90;

	/* LayerAgl */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__8LayerAglSFv = 0x106EC05C;
	typeInfo__L0__getRuntimeTypeInfoStatic__8LayerAglSFv = 0x106EC270;
	__ct__8LayerAglFv = 0xF0B9290;

	/* LayerAgl::Node */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_8LayerAgl4NodeSFv = 0x106EBF00;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_8LayerAgl4NodeSFv = 0x106EC194;

	/* ObjLayer */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__8ObjLayerSFv = 0x106EC060;
	typeInfo__L0__getRuntimeTypeInfoStatic__8ObjLayerSFv = 0x106EC274;
	setParentRenderer__8ObjLayerFP16ObjLayerRenderer = 0xF0BCA24;

	/* ObjLayer::Node */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_8ObjLayer4NodeSFv = 0x106EBF04;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_8ObjLayer4NodeSFv = 0x106EC198;

	/* RenderObjLayer */
	__ct__14RenderObjLayerFv = 0xF0BCA6C;

	/* RenderObjLayer::Node */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_14RenderObjLayer4NodeSFv = 0x106EBF08;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_14RenderObjLayer4NodeSFv = 0x106EC19C;

	/* CourseSelectTask::Layer2D */
	__vtbl__Q2_16CourseSelectTask7Layer2D = 0x10549218;

	/* ControllerWrapper */
	__ct__17ControllerWrapperFv = 0xF0D4150;
	__dt__17ControllerWrapperFv = 0xF0D40E8;
	registerWith__17ControllerWrapperFQ2_14GameController2Id = 0xF0D41B0;

	/* ObjLayerRenderer */
	__ct__16ObjLayerRendererFRCQ2_4sead23SafeStringBase__tm__2_c = 0xF0BAF58;
	init__16ObjLayerRendererFUiN31PQ2_4sead4Heap = 0xF0BB128;

	/* Misc */
	BLOSDynLoad_Acquire = 0xF65EF58;
	BOSDynLoad_FindExport = 0xF65F418;
	PlayerJumpArc = 0x1066CA00;
	MiniPlayerJumpArc = 0x1066CA48;
	PlayerJumpMax = 0x10669068;
	PlayerDescentRate = 0x10669074;
	DefaultReverbHiParam = 0x1072F528;
	DefaultDelayParam = 0x1072F554;
	SFXReverb_0 = 0x106E9F14;
	SFXReverb_1 = 0x106E9F18;
	SFXReverbPlyJump_0 = 0x106E9F1C;
	SFXReverbPlyJump_1 = 0x106E9F20;

}