declare i32 @putchar(i32)
declare void @logInitMgba()
declare void @logOutputMgba(i8 %level, ptr %msg)

@.msg = private unnamed_addr constant [9 x i8] c"hellord\0"

define void @main() {
  call void @logInitMgba()
  call void @logOutputMgba(i8 2, ptr @.msg)
  ret void
}

