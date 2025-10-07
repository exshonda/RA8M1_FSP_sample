#include "guard.h"

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_open_guard(uart_ctrl_t *const p_api_ctrl, uart_cfg_t const *const p_cfg)
{
    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);
    FSP_PARAMETER_NOT_USED (p_cfg);

    return R_SCI_B_UART_Open (&g_uart0_ctrl, &g_uart0_cfg);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_read_guard(uart_ctrl_t *const p_api_ctrl, uint8_t *const p_dest,
        uint32_t const bytes)
{
    /* Verify all pointers are in non-secure memory. */
    uint8_t *const p_dest_checked = cmse_check_address_range ((void*) p_dest, bytes, CMSE_AU_NONSECURE);
    FSP_ASSERT (p_dest_checked != NULL);

    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);

    return R_SCI_B_UART_Read (&g_uart0_ctrl, p_dest_checked, bytes);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_write_guard(uart_ctrl_t *const p_api_ctrl, uint8_t const *const p_src,
        uint32_t const bytes)
{
    /* Verify all pointers are in non-secure memory. */
    uint8_t const *const p_src_checked = cmse_check_address_range ((void*) p_src, bytes, CMSE_AU_NONSECURE);
    FSP_ASSERT (p_src_checked != NULL);

    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);

    return R_SCI_B_UART_Write (&g_uart0_ctrl, p_src_checked, bytes);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_baud_set_guard(uart_ctrl_t *const p_api_ctrl,
        void const *const p_baud_setting)
{
    /* Verify all pointers are in non-secure memory. */
    void const *const p_baud_setting_checked = cmse_check_address_range ((void*) p_baud_setting,
                                                                         sizeof(sci_b_baud_setting_t),
                                                                         CMSE_AU_NONSECURE);
    FSP_ASSERT (p_baud_setting_checked != NULL);

    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);

    return R_SCI_B_UART_BaudSet (&g_uart0_ctrl, p_baud_setting_checked);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_info_get_guard(uart_ctrl_t *const p_api_ctrl, uart_info_t *const p_info)
{
    /* Verify all pointers are in non-secure memory. */
    uart_info_t *const p_info_checked = cmse_check_pointed_object (p_info, CMSE_AU_NONSECURE);
    FSP_ASSERT (p_info_checked != NULL);

    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);

    return R_SCI_B_UART_InfoGet (&g_uart0_ctrl, p_info_checked);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_close_guard(uart_ctrl_t *const p_api_ctrl)
{
    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);

    return R_SCI_B_UART_Close (&g_uart0_ctrl);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_abort_guard(uart_ctrl_t *const p_api_ctrl, uart_dir_t communication_to_abort)
{
    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);

    return R_SCI_B_UART_Abort (&g_uart0_ctrl, communication_to_abort);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_baud_calculate_guard(uint32_t baudrate, bool bitrate_modulation,
        uint32_t baud_rate_error_x_1000, sci_b_baud_setting_t *const p_baud_setting)
{
    /* Verify all pointers are in non-secure memory. */
    sci_b_baud_setting_t *const p_baud_setting_checked = cmse_check_pointed_object (p_baud_setting, CMSE_AU_NONSECURE);
    FSP_ASSERT (p_baud_setting_checked != NULL);

    /* TODO: add your own security checks here */

    return R_SCI_B_UART_BaudCalculate (baudrate, bitrate_modulation, baud_rate_error_x_1000, p_baud_setting_checked);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_callback_set_guard(uart_ctrl_t *const p_api_ctrl,
        void (*p_callback)(uart_callback_args_t*), void *const p_context, uart_callback_args_t *const p_callback_memory)
{
    /* Verify all pointers are in non-secure memory. */
    void (*p_callback_checked)(
            uart_callback_args_t*) = (void(*)(uart_callback_args_t *)) cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE);
    FSP_ASSERT(p_callback_checked != NULL);
    uart_callback_args_t *const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory, CMSE_AU_NONSECURE);
    FSP_ASSERT(p_callback_memory_checked != NULL);

    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_context);

    return R_SCI_B_UART_CallbackSet(&g_uart0_ctrl, p_callback_checked, p_context, p_callback_memory_checked);
}

BSP_CMSE_NONSECURE_ENTRY fsp_err_t g_uart0_read_stop_guard(uart_ctrl_t *const p_api_ctrl, uint32_t *remaining_bytes)
{
    /* Verify all pointers are in non-secure memory. */
    uint32_t *remaining_bytes_checked = cmse_check_address_range ((void*) remaining_bytes, sizeof(uint32_t),
                                                                  CMSE_AU_NONSECURE);
    FSP_ASSERT (remaining_bytes_checked != NULL);

    /* TODO: add your own security checks here */

    FSP_PARAMETER_NOT_USED (p_api_ctrl);

    return R_SCI_B_UART_ReadStop (&g_uart0_ctrl, remaining_bytes_checked);
}
