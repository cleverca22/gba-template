declare void @logInitMgba()
declare void @logOutputMgba(i8 %level, ptr %msg)

@.msg = private unnamed_addr constant [9 x i8] c"hellord\0"

define void @main() {
  ; call void @logInitMgba()
  call i1 @log_init()
  call void @logOutputMgba(i8 4, ptr @.msg)
  ret void
}

define i1 @log_init() {
  store volatile i16  -16162, i16* inttoptr(i32 83883904 to i16*)
  %1 = load volatile i16, i16* inttoptr (i64 83883904 to i16*)
  %2 = icmp eq i16 %1, 7658
  ret i1 %2
}
