declare void @logInitMgba()
declare void @logOutputMgba(i8 %level, ptr %msg)
declare void @draw()
declare void @mainloop()

@.msg = private unnamed_addr constant [8 x i8] c"hellord\00"

define void @main() {
  ; call void @logInitMgba()
  call i1 @log_init()
  call void @logOutputMgba(i8 4, ptr @.msg)
  call void @draw()
  call void @mainloop()
  ret void
}

define i1 @log_init() {
  store volatile i16  -16162, i16* inttoptr(i32 83883904 to i16*)
  %1 = load volatile i16, i16* inttoptr (i64 83883904 to i16*)
  %2 = icmp eq i16 %1, 7658
  ret i1 %2
}
