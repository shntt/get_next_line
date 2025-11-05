/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shitakah <shitakah@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 02:27:27 by shitakah          #+#    #+#             */
/*   Updated: 2025/11/06 00:03:18 by shitakah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line_buffer(int fd, char *left_c, char *buffer);
static char	*set_line(char *line_buffer);

char	*get_next_line(int fd)
{
	size_t	bufsize;

	bufsize = 42;
	
}

static char	*fill_line_buffer(int fd, char *left_c, char *buffer);

static char	*set_line(char *line_buffer);

int	main(void)
{

}

// 1. fdが渡される
// 2. （初回だけ）読み込み開始用のstatic変数 ptr を初期化
// 3. ptr から \n or \0まで、malloc領域 res に複製、ポインターを返す
//		static set_line
//	 		malloc(sizeof(char) * bufsize(+1?))した領域bufにreadで保存
//  			＊read は保存領域bufとバイト数byteを指定する必要がある
//			そのあと、bufに \n or \0 が存在しないかチェック
//				存在しなければ、長さだけ保存して、再度read
//				存在したら、切り分けて、
//					前半は、長さを加算。後半はstatic変数 ptr に（\0を加え）保存
//						ptr は tmp に逃がしておく
//					いや、長さをカウントするんじゃなく、catするべきかも
//						そうすればfreeできる。でもmallocをさらに増やしている
//				buf は用済みなのでfree
//		static fill_line_buffer
//			長さでmalloc、元のptrから長さ分、複製する
//		strchr, strdup, strlen, substr, strjoin
