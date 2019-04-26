#include <iostream>
#include <unistd.h>

void *printInt(void *args);
void *handle_test_value(void *args);

//定义10个线程
#define THREAD_NUMS  10

int test_value=0;

pthread_mutex_t mutex; //声明互斥锁标识符


int mainss() {

    //1.建立场景, 同事执行多个线程, 打印数字
    pthread_t ptIds[THREAD_NUMS];
    pthread_attr_t patId;


    //互斥锁 init, 第二个参数为设置互斥锁的属性, 这里不需要
    int m_ret = pthread_mutex_init(&mutex, NULL);

    if (m_ret){
        std::cout << "pthread_mutex_init error --> " << m_ret << std::endl;
        return -1;
    }

    //创建10个线程
    for (int i = 0; i < THREAD_NUMS; ++i) {

        /**
         * 1.指向线程标识符的指针
         * 2.用来设置线程属性
         * 3.运行函数的其实地址
         * 4.运行函数的参数
         */
//        int ret = pthread_create(&ptIds[i], NULL, printInt, &i);
        int ret = pthread_create(&ptIds[i], NULL, handle_test_value, NULL);
//        std::cout << "ret => " << ret << std::endl;
        if (ret) {
            printf("error : %d", ret);
            return -1;
        }
    }

    /**
     * 为了让所有线程都创建完毕
     */
//    1.sleep(15);


//    2.使用pthread_join同步, 保证所有线程执行完后再退出
    for (int j = 0; j < THREAD_NUMS; ++j) {
        pthread_join(ptIds[j], NULL);
    }

    /**
     * pthread_join解析:
     * 1.如果没有使用 pthread_join, 这里的 main 方法一瞬间就结束了, 因为主线程是和子线程相互运行不受影响, 是异步的
     * 这回导致什么后果呢, 就是子线程创建了, 准备运行的时候, 主线程已经结束了,
     * 所以使用 pthread_join 可以解决这个问题
     * 使用 pthread_join 后, 主线程会一直等待, 直到 pthread_join 的线程都结束后, 自己才会结束
     *
     */


    //销毁锁
    pthread_mutex_destroy(&mutex);

    std::cout << "finished" << std::endl;

    return 0;
}


/**
 * 每个线程休眠1s,第二秒时, 其实所有线程都已经创建完毕, 那么i 此时已经10 了, 所以这个方法全部打印出 10
 * @param args
 * @return
 */
void *printInt(void *args) {
    int thread_arg;
    sleep(1);
    /**
     * 1.args-->(int *) 转为 int 指针类型
     * 2.*(int *) 用*取出 int 值
     * 3.再用 int 强转为 int 类型
     */
    thread_arg = (int(*(int *) args));
    std::cout << "Thread print ----> " << thread_arg << std::endl;

}


/**
 * 在没加锁之前, 打印出来是乱的,顺序不是从 1--->10
 * @param args
 * @return
 */
void *handle_test_value(void *args)
{


    int ret = pthread_mutex_lock(&mutex);
    if (ret){
        std::cout << "pthread_mutex_lock error --> " << ret << std::endl;
        exit(ret);
    }
    test_value++;
    printf("test value ----> %d \n", test_value);
    sleep(1);
    pthread_mutex_unlock(&mutex);

//    std::cout << "test value ----> " << test_value++ << std::endl;

}