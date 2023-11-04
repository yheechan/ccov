; ModuleID = 'example.c'
source_filename = "example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@static_var = dso_local global i32 1, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @f1(i32 %a) #0 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  %0 = load i32, i32* @static_var, align 4
  %inc = add nsw i32 %0, 1
  store i32 %inc, i32* @static_var, align 4
  %1 = load i32, i32* %a.addr, align 4
  %cmp = icmp eq i32 %1, 1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i32 2, i32* %retval, align 4
  br label %return

if.else:                                          ; preds = %entry
  store i32 4, i32* %retval, align 4
  br label %return

return:                                           ; preds = %if.else, %if.then
  %2 = load i32, i32* %retval, align 4
  ret i32 %2
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 0, i32* %a, align 4
  %0 = load i32, i32* %a, align 4
  %call = call i32 @f1(i32 %0)
  store i32 %call, i32* %a, align 4
  %1 = load i32, i32* %a, align 4
  %cmp = icmp eq i32 %1, 1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  store i32 2, i32* %a, align 4
  br label %if.end4

if.else:                                          ; preds = %entry
  %2 = load i32, i32* %a, align 4
  %cmp1 = icmp eq i32 %2, 2
  br i1 %cmp1, label %if.then2, label %if.else3

if.then2:                                         ; preds = %if.else
  store i32 1, i32* %a, align 4
  br label %if.end

if.else3:                                         ; preds = %if.else
  store i32 4, i32* %a, align 4
  br label %if.end

if.end:                                           ; preds = %if.else3, %if.then2
  br label %if.end4

if.end4:                                          ; preds = %if.end, %if.then
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %if.end4
  %3 = load i32, i32* %i, align 4
  %cmp5 = icmp slt i32 %3, 10
  br i1 %cmp5, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4
  %5 = load i32, i32* %a, align 4
  %add = add nsw i32 %5, %4
  store i32 %add, i32* %a, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %6 = load i32, i32* %i, align 4
  %inc = add nsw i32 %6, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond, !llvm.loop !4

for.end:                                          ; preds = %for.cond
  br label %while.cond

while.cond:                                       ; preds = %while.body, %for.end
  %7 = load i32, i32* %a, align 4
  %cmp6 = icmp slt i32 %7, 100
  br i1 %cmp6, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %8 = load i32, i32* %a, align 4
  %9 = load i32, i32* %a, align 4
  %add7 = add nsw i32 %9, %8
  store i32 %add7, i32* %a, align 4
  br label %while.cond, !llvm.loop !6

while.end:                                        ; preds = %while.cond
  br label %do.body

do.body:                                          ; preds = %do.cond, %while.end
  %10 = load i32, i32* %a, align 4
  switch i32 %10, label %sw.default [
    i32 100, label %sw.bb
    i32 200, label %sw.bb9
  ]

sw.bb:                                            ; preds = %do.body
  %11 = load i32, i32* %a, align 4
  %add8 = add nsw i32 %11, 10
  store i32 %add8, i32* %a, align 4
  br label %sw.epilog

sw.bb9:                                           ; preds = %do.body
  %12 = load i32, i32* %a, align 4
  %cmp10 = icmp eq i32 %12, 3
  %13 = zext i1 %cmp10 to i64
  %cond = select i1 %cmp10, i32 1, i32 2
  store i32 %cond, i32* %a, align 4
  %14 = load i32, i32* %a, align 4
  %add11 = add nsw i32 %14, 20
  store i32 %add11, i32* %a, align 4
  br label %sw.epilog

sw.default:                                       ; preds = %do.body
  %15 = load i32, i32* %a, align 4
  %add12 = add nsw i32 %15, 1
  store i32 %add12, i32* %a, align 4
  br label %sw.epilog

sw.epilog:                                        ; preds = %sw.default, %sw.bb9, %sw.bb
  br label %do.cond

do.cond:                                          ; preds = %sw.epilog
  %16 = load i32, i32* %a, align 4
  %cmp13 = icmp eq i32 %16, 0
  %lnot = xor i1 %cmp13, true
  br i1 %lnot, label %do.body, label %do.end, !llvm.loop !7

do.end:                                           ; preds = %do.cond
  %17 = load i32, i32* %a, align 4
  switch i32 %17, label %sw.epilog18 [
    i32 150, label %sw.bb14
    i32 250, label %sw.bb16
  ]

sw.bb14:                                          ; preds = %do.end
  %18 = load i32, i32* %a, align 4
  %add15 = add nsw i32 %18, 20
  store i32 %add15, i32* %a, align 4
  br label %sw.epilog18

sw.bb16:                                          ; preds = %do.end
  %19 = load i32, i32* %a, align 4
  %add17 = add nsw i32 %19, 30
  store i32 %add17, i32* %a, align 4
  br label %sw.epilog18

sw.epilog18:                                      ; preds = %do.end, %sw.bb16, %sw.bb14
  %20 = load i32, i32* %retval, align 4
  ret i32 %20
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"Ubuntu clang version 13.0.1-++20220120110844+75e33f71c2da-1~exp1~20220120230854.66"}
!4 = distinct !{!4, !5}
!5 = !{!"llvm.loop.mustprogress"}
!6 = distinct !{!6, !5}
!7 = distinct !{!7, !5}
