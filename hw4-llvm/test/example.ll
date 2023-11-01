; ModuleID = 'test/example.c'
source_filename = "test/example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.HelloWorld = type { i32, i32, i32 }

@static_var = dso_local global i32 1, align 4, !dbg !0
@hw = dso_local global [10 x %struct.HelloWorld] zeroinitializer, align 16, !dbg !6
@MyStructName = external global { i32, i32, i32, i32 }
@ssT = external global [10 x { i32, i32, i32, i32 }]
@0 = private unnamed_addr constant [3 x i8] c"f1\00", align 1
@1 = private unnamed_addr constant [3 x i8] c"f1\00", align 1
@2 = private unnamed_addr constant [3 x i8] c"f1\00", align 1
@3 = private unnamed_addr constant [3 x i8] c"f1\00", align 1
@4 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@5 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@6 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@7 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@8 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@9 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@10 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@11 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@12 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@13 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@14 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@15 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@16 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@17 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@18 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@19 = private unnamed_addr constant [5 x i8] c"main\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @f1(i32 %a) #0 !dbg !23 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca i32, align 4
  call void @_probe_(i32 -1, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32 %a)
  store i32 %a, i32* %a.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %a.addr, metadata !26, metadata !DIExpression()), !dbg !27
  %0 = load i32, i32* @static_var, align 4, !dbg !28
  %inc = add nsw i32 %0, 1, !dbg !28
  call void @_probe_(i32 13, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32 %inc), !dbg !28
  store i32 %inc, i32* @static_var, align 4, !dbg !28
  %1 = load i32, i32* %a.addr, align 4, !dbg !29
  %cmp = icmp eq i32 %1, 1, !dbg !31
  br i1 %cmp, label %if.then, label %if.else, !dbg !32

if.then:                                          ; preds = %entry
  call void @_probe_(i32 16, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i32 2), !dbg !33
  store i32 2, i32* %retval, align 4, !dbg !33
  br label %return, !dbg !33

if.else:                                          ; preds = %entry
  call void @_probe_(i32 18, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @3, i32 0, i32 0), i32 4), !dbg !35
  store i32 4, i32* %retval, align 4, !dbg !35
  br label %return, !dbg !35

return:                                           ; preds = %if.else, %if.then
  %2 = load i32, i32* %retval, align 4, !dbg !37
  ret i32 %2, !dbg !37
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !38 {
entry:
  call void @_init_()
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  call void @_probe_(i32 -1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @4, i32 0, i32 0), i32 0)
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %a, metadata !41, metadata !DIExpression()), !dbg !42
  call void @_probe_(i32 23, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @5, i32 0, i32 0), i32 0), !dbg !42
  store i32 0, i32* %a, align 4, !dbg !42
  %0 = load i32, i32* %a, align 4, !dbg !43
  %call = call i32 @f1(i32 %0), !dbg !44
  call void @_probe_(i32 24, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @6, i32 0, i32 0), i32 %call), !dbg !45
  store i32 %call, i32* %a, align 4, !dbg !45
  %1 = load i32, i32* %a, align 4, !dbg !46
  %cmp = icmp eq i32 %1, 1, !dbg !48
  br i1 %cmp, label %if.then, label %if.else, !dbg !49

if.then:                                          ; preds = %entry
  call void @_probe_(i32 27, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @7, i32 0, i32 0), i32 2), !dbg !50
  store i32 2, i32* %a, align 4, !dbg !50
  br label %if.end4, !dbg !52

if.else:                                          ; preds = %entry
  %2 = load i32, i32* %a, align 4, !dbg !53
  %cmp1 = icmp eq i32 %2, 2, !dbg !55
  br i1 %cmp1, label %if.then2, label %if.else3, !dbg !56

if.then2:                                         ; preds = %if.else
  call void @_probe_(i32 29, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @8, i32 0, i32 0), i32 1), !dbg !57
  store i32 1, i32* %a, align 4, !dbg !57
  br label %if.end, !dbg !59

if.else3:                                         ; preds = %if.else
  call void @_probe_(i32 31, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @9, i32 0, i32 0), i32 4), !dbg !60
  store i32 4, i32* %a, align 4, !dbg !60
  br label %if.end

if.end:                                           ; preds = %if.else3, %if.then2
  br label %if.end4

if.end4:                                          ; preds = %if.end, %if.then
  call void @llvm.dbg.declare(metadata i32* %i, metadata !62, metadata !DIExpression()), !dbg !64
  call void @_probe_(i32 35, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @10, i32 0, i32 0), i32 0), !dbg !64
  store i32 0, i32* %i, align 4, !dbg !64
  br label %for.cond, !dbg !65

for.cond:                                         ; preds = %for.inc, %if.end4
  %3 = load i32, i32* %i, align 4, !dbg !66
  %cmp5 = icmp slt i32 %3, 10, !dbg !68
  br i1 %cmp5, label %for.body, label %for.end, !dbg !69

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4, !dbg !70
  %5 = load i32, i32* %a, align 4, !dbg !72
  %add = add nsw i32 %5, %4, !dbg !72
  call void @_probe_(i32 36, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @11, i32 0, i32 0), i32 %add), !dbg !72
  store i32 %add, i32* %a, align 4, !dbg !72
  br label %for.inc, !dbg !73

for.inc:                                          ; preds = %for.body
  %6 = load i32, i32* %i, align 4, !dbg !74
  %inc = add nsw i32 %6, 1, !dbg !74
  call void @_probe_(i32 35, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @12, i32 0, i32 0), i32 %inc), !dbg !74
  store i32 %inc, i32* %i, align 4, !dbg !74
  br label %for.cond, !dbg !75, !llvm.loop !76

for.end:                                          ; preds = %for.cond
  br label %while.cond, !dbg !79

while.cond:                                       ; preds = %while.body, %for.end
  %7 = load i32, i32* %a, align 4, !dbg !80
  %cmp6 = icmp slt i32 %7, 100, !dbg !81
  br i1 %cmp6, label %while.body, label %while.end, !dbg !79

while.body:                                       ; preds = %while.cond
  %8 = load i32, i32* %a, align 4, !dbg !82
  %9 = load i32, i32* %a, align 4, !dbg !84
  %add7 = add nsw i32 %9, %8, !dbg !84
  call void @_probe_(i32 41, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @13, i32 0, i32 0), i32 %add7), !dbg !84
  store i32 %add7, i32* %a, align 4, !dbg !84
  br label %while.cond, !dbg !79, !llvm.loop !85

while.end:                                        ; preds = %while.cond
  br label %do.body, !dbg !87

do.body:                                          ; preds = %do.cond, %while.end
  %10 = load i32, i32* %a, align 4, !dbg !88
  switch i32 %10, label %sw.default [
    i32 100, label %sw.bb
    i32 200, label %sw.bb9
  ], !dbg !90

sw.bb:                                            ; preds = %do.body
  %11 = load i32, i32* %a, align 4, !dbg !91
  %add8 = add nsw i32 %11, 10, !dbg !91
  call void @_probe_(i32 48, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @14, i32 0, i32 0), i32 %add8), !dbg !91
  store i32 %add8, i32* %a, align 4, !dbg !91
  br label %sw.epilog, !dbg !93

sw.bb9:                                           ; preds = %do.body
  %12 = load i32, i32* %a, align 4, !dbg !94
  %cmp10 = icmp eq i32 %12, 3, !dbg !95
  %13 = zext i1 %cmp10 to i64, !dbg !94
  %cond = select i1 %cmp10, i32 1, i32 2, !dbg !94
  call void @_probe_(i32 51, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @15, i32 0, i32 0), i32 %cond), !dbg !96
  store i32 %cond, i32* %a, align 4, !dbg !96
  %14 = load i32, i32* %a, align 4, !dbg !97
  %add11 = add nsw i32 %14, 20, !dbg !97
  call void @_probe_(i32 52, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @16, i32 0, i32 0), i32 %add11), !dbg !97
  store i32 %add11, i32* %a, align 4, !dbg !97
  br label %sw.epilog, !dbg !98

sw.default:                                       ; preds = %do.body
  %15 = load i32, i32* %a, align 4, !dbg !99
  %add12 = add nsw i32 %15, 1, !dbg !99
  call void @_probe_(i32 55, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @17, i32 0, i32 0), i32 %add12), !dbg !99
  store i32 %add12, i32* %a, align 4, !dbg !99
  br label %sw.epilog, !dbg !100

sw.epilog:                                        ; preds = %sw.default, %sw.bb9, %sw.bb
  br label %do.cond, !dbg !101

do.cond:                                          ; preds = %sw.epilog
  %16 = load i32, i32* %a, align 4, !dbg !102
  %cmp13 = icmp eq i32 %16, 0, !dbg !103
  br i1 %cmp13, label %do.body, label %do.end, !dbg !101, !llvm.loop !104

do.end:                                           ; preds = %do.cond
  %17 = load i32, i32* %a, align 4, !dbg !106
  switch i32 %17, label %sw.epilog18 [
    i32 150, label %sw.bb14
    i32 250, label %sw.bb16
  ], !dbg !107

sw.bb14:                                          ; preds = %do.end
  %18 = load i32, i32* %a, align 4, !dbg !108
  %add15 = add nsw i32 %18, 20, !dbg !108
  call void @_probe_(i32 61, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @18, i32 0, i32 0), i32 %add15), !dbg !108
  store i32 %add15, i32* %a, align 4, !dbg !108
  br label %sw.epilog18, !dbg !110

sw.bb16:                                          ; preds = %do.end
  %19 = load i32, i32* %a, align 4, !dbg !111
  %add17 = add nsw i32 %19, 30, !dbg !111
  call void @_probe_(i32 64, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @19, i32 0, i32 0), i32 %add17), !dbg !111
  store i32 %add17, i32* %a, align 4, !dbg !111
  br label %sw.epilog18, !dbg !112

sw.epilog18:                                      ; preds = %do.end, %sw.bb16, %sw.bb14
  %20 = load i32, i32* %retval, align 4, !dbg !113
  ret i32 %20, !dbg !113
}

declare void @_init_()

declare void @_probe_(i32, i8*, i32)

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!17, !18, !19, !20, !21}
!llvm.ident = !{!22}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "static_var", scope: !2, file: !3, line: 2, type: !12, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "Ubuntu clang version 13.0.1-++20220120110844+75e33f71c2da-1~exp1~20220120230854.66", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "test/example.c", directory: "/home/yangheechan/23-2/llvm-ir-kcov/hw4-llvm")
!4 = !{}
!5 = !{!0, !6}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "hw", scope: !2, file: !3, line: 10, type: !8, isLocal: false, isDefinition: true)
!8 = !DICompositeType(tag: DW_TAG_array_type, baseType: !9, size: 960, elements: !15)
!9 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "HelloWorld", file: !3, line: 4, size: 96, elements: !10)
!10 = !{!11, !13, !14}
!11 = !DIDerivedType(tag: DW_TAG_member, name: "x", scope: !9, file: !3, line: 5, baseType: !12, size: 32)
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "y", scope: !9, file: !3, line: 6, baseType: !12, size: 32, offset: 32)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "z", scope: !9, file: !3, line: 7, baseType: !12, size: 32, offset: 64)
!15 = !{!16}
!16 = !DISubrange(count: 10)
!17 = !{i32 7, !"Dwarf Version", i32 4}
!18 = !{i32 2, !"Debug Info Version", i32 3}
!19 = !{i32 1, !"wchar_size", i32 4}
!20 = !{i32 7, !"uwtable", i32 1}
!21 = !{i32 7, !"frame-pointer", i32 2}
!22 = !{!"Ubuntu clang version 13.0.1-++20220120110844+75e33f71c2da-1~exp1~20220120230854.66"}
!23 = distinct !DISubprogram(name: "f1", scope: !3, file: !3, line: 12, type: !24, scopeLine: 12, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!24 = !DISubroutineType(types: !25)
!25 = !{!12, !12}
!26 = !DILocalVariable(name: "a", arg: 1, scope: !23, file: !3, line: 12, type: !12)
!27 = !DILocation(line: 12, column: 12, scope: !23)
!28 = !DILocation(line: 13, column: 12, scope: !23)
!29 = !DILocation(line: 15, column: 6, scope: !30)
!30 = distinct !DILexicalBlock(scope: !23, file: !3, line: 15, column: 6)
!31 = !DILocation(line: 15, column: 8, scope: !30)
!32 = !DILocation(line: 15, column: 6, scope: !23)
!33 = !DILocation(line: 16, column: 3, scope: !34)
!34 = distinct !DILexicalBlock(scope: !30, file: !3, line: 15, column: 14)
!35 = !DILocation(line: 18, column: 3, scope: !36)
!36 = distinct !DILexicalBlock(scope: !30, file: !3, line: 17, column: 9)
!37 = !DILocation(line: 20, column: 1, scope: !23)
!38 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 22, type: !39, scopeLine: 22, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!39 = !DISubroutineType(types: !40)
!40 = !{!12}
!41 = !DILocalVariable(name: "a", scope: !38, file: !3, line: 23, type: !12)
!42 = !DILocation(line: 23, column: 6, scope: !38)
!43 = !DILocation(line: 24, column: 9, scope: !38)
!44 = !DILocation(line: 24, column: 6, scope: !38)
!45 = !DILocation(line: 24, column: 4, scope: !38)
!46 = !DILocation(line: 26, column: 6, scope: !47)
!47 = distinct !DILexicalBlock(scope: !38, file: !3, line: 26, column: 6)
!48 = !DILocation(line: 26, column: 8, scope: !47)
!49 = !DILocation(line: 26, column: 6, scope: !38)
!50 = !DILocation(line: 27, column: 5, scope: !51)
!51 = distinct !DILexicalBlock(scope: !47, file: !3, line: 26, column: 14)
!52 = !DILocation(line: 28, column: 2, scope: !51)
!53 = !DILocation(line: 28, column: 14, scope: !54)
!54 = distinct !DILexicalBlock(scope: !47, file: !3, line: 28, column: 14)
!55 = !DILocation(line: 28, column: 16, scope: !54)
!56 = !DILocation(line: 28, column: 14, scope: !47)
!57 = !DILocation(line: 29, column: 5, scope: !58)
!58 = distinct !DILexicalBlock(scope: !54, file: !3, line: 28, column: 21)
!59 = !DILocation(line: 30, column: 2, scope: !58)
!60 = !DILocation(line: 31, column: 5, scope: !61)
!61 = distinct !DILexicalBlock(scope: !54, file: !3, line: 30, column: 9)
!62 = !DILocalVariable(name: "i", scope: !63, file: !3, line: 35, type: !12)
!63 = distinct !DILexicalBlock(scope: !38, file: !3, line: 35, column: 2)
!64 = !DILocation(line: 35, column: 11, scope: !63)
!65 = !DILocation(line: 35, column: 7, scope: !63)
!66 = !DILocation(line: 35, column: 19, scope: !67)
!67 = distinct !DILexicalBlock(scope: !63, file: !3, line: 35, column: 2)
!68 = !DILocation(line: 35, column: 21, scope: !67)
!69 = !DILocation(line: 35, column: 2, scope: !63)
!70 = !DILocation(line: 36, column: 8, scope: !71)
!71 = distinct !DILexicalBlock(scope: !67, file: !3, line: 35, column: 34)
!72 = !DILocation(line: 36, column: 5, scope: !71)
!73 = !DILocation(line: 37, column: 2, scope: !71)
!74 = !DILocation(line: 35, column: 29, scope: !67)
!75 = !DILocation(line: 35, column: 2, scope: !67)
!76 = distinct !{!76, !69, !77, !78}
!77 = !DILocation(line: 37, column: 2, scope: !63)
!78 = !{!"llvm.loop.mustprogress"}
!79 = !DILocation(line: 40, column: 2, scope: !38)
!80 = !DILocation(line: 40, column: 9, scope: !38)
!81 = !DILocation(line: 40, column: 11, scope: !38)
!82 = !DILocation(line: 41, column: 8, scope: !83)
!83 = distinct !DILexicalBlock(scope: !38, file: !3, line: 40, column: 19)
!84 = !DILocation(line: 41, column: 5, scope: !83)
!85 = distinct !{!85, !79, !86, !78}
!86 = !DILocation(line: 42, column: 2, scope: !38)
!87 = !DILocation(line: 45, column: 2, scope: !38)
!88 = !DILocation(line: 46, column: 10, scope: !89)
!89 = distinct !DILexicalBlock(scope: !38, file: !3, line: 45, column: 5)
!90 = !DILocation(line: 46, column: 3, scope: !89)
!91 = !DILocation(line: 48, column: 7, scope: !92)
!92 = distinct !DILexicalBlock(scope: !89, file: !3, line: 46, column: 13)
!93 = !DILocation(line: 49, column: 5, scope: !92)
!94 = !DILocation(line: 51, column: 9, scope: !92)
!95 = !DILocation(line: 51, column: 11, scope: !92)
!96 = !DILocation(line: 51, column: 7, scope: !92)
!97 = !DILocation(line: 52, column: 7, scope: !92)
!98 = !DILocation(line: 53, column: 5, scope: !92)
!99 = !DILocation(line: 55, column: 7, scope: !92)
!100 = !DILocation(line: 56, column: 3, scope: !92)
!101 = !DILocation(line: 57, column: 2, scope: !89)
!102 = !DILocation(line: 57, column: 11, scope: !38)
!103 = !DILocation(line: 57, column: 13, scope: !38)
!104 = distinct !{!104, !87, !105, !78}
!105 = !DILocation(line: 57, column: 18, scope: !38)
!106 = !DILocation(line: 59, column: 9, scope: !38)
!107 = !DILocation(line: 59, column: 2, scope: !38)
!108 = !DILocation(line: 61, column: 5, scope: !109)
!109 = distinct !DILexicalBlock(scope: !38, file: !3, line: 59, column: 12)
!110 = !DILocation(line: 62, column: 4, scope: !109)
!111 = !DILocation(line: 64, column: 5, scope: !109)
!112 = !DILocation(line: 65, column: 4, scope: !109)
!113 = !DILocation(line: 67, column: 1, scope: !38)
