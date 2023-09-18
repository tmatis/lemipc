#include <pthread.h>
#include <ft_logs.h>
#include <bool_t.h>

static pthread_mutex_t force_stop_mutex = PTHREAD_MUTEX_INITIALIZER;
static bool_t force_stop_flag = false;

/**
 * @brief Set the force stop flag
*/
void force_stop(void)
{
    pthread_mutex_lock(&force_stop_mutex);
    ft_log(LOG_LEVEL_WARNING, "forced stop scheduled");
    force_stop_flag = true;
    pthread_mutex_unlock(&force_stop_mutex);
}

/**
 * @brief Check if the force stop flag is set
 * 
 * @return bool_t
 */
bool_t force_stop_is_set(void)
{
    bool_t ret;
    pthread_mutex_lock(&force_stop_mutex);
    ret = force_stop_flag;
    pthread_mutex_unlock(&force_stop_mutex);
    return (ret);
}