; ModuleID = 'example1.c'
source_filename = "example1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %z = alloca i32, align 4
  %k = alloca i32, align 4
  %l = alloca i32, align 4
  %m = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 1, i32* %x, align 4
  store i32 3, i32* %y, align 4
  store i32 43, i32* %z, align 4
  store i32 21, i32* %k, align 4
  store i32 17, i32* %l, align 4
  store i32 22, i32* %m, align 4
  %0 = load i32, i32* %x, align 4
  %tobool = icmp ne i32 %0, 0
  br i1 %tobool, label %land.lhs.true, label %if.else

land.lhs.true:                                    ; preds = %entry
  %1 = load i32, i32* %y, align 4
  %rem = srem i32 %1, 2
  %cmp = icmp eq i32 %rem, 0
  br i1 %cmp, label %land.lhs.true1, label %if.else

land.lhs.true1:                                   ; preds = %land.lhs.true
  %2 = load i32, i32* %z, align 4
  %3 = load i32, i32* %k, align 4
  %sub = sub nsw i32 %2, %3
  %4 = load i32, i32* %l, align 4
  %5 = load i32, i32* %m, align 4
  %sub2 = sub nsw i32 %4, %5
  %cmp3 = icmp sge i32 %sub, %sub2
  br i1 %cmp3, label %if.then, label %if.else

if.then:                                          ; preds = %land.lhs.true1
  store i32 3, i32* %z, align 4
  br label %if.end

if.else:                                          ; preds = %land.lhs.true1, %land.lhs.true, %entry
  store i32 7, i32* %z, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %6 = load i32, i32* %retval, align 4
  ret i32 %6
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"Ubuntu clang version 13.0.1-++20220120110844+75e33f71c2da-1~exp1~20220120230854.66"}
