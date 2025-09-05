// void ti_enter_critical(void) {
//   int32_t* const critical_count = 
//       ti_get_this_core() == TI_CORE_ID_CM7 ? 
//       &_cm7_critical_count : &_cm4_critical_count;
//   if (*critical_count == 0) {
//     asm volatile ("cpsid i");
//   }
//   (*critical_count)++;
// }

// void ti_exit_critical(void) {
//   int32_t* const critical_count = 
//       ti_get_this_core() == TI_CORE_ID_CM7 ? 
//       &_cm7_critical_count : &_cm4_critical_count;
//   if (*critical_count > 0) {
//     (*critical_count)--;
//     if (*critical_count == 0) {
//       asm volatile ("cpsie i");
//     }
//   }
// }

// void ti_enter_exclusive(void) {
//   // TODO
// }

// void ti_exit_exclusive(void) {
//   // TODO
// }