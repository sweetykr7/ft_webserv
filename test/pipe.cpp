#include <stdexcept>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

// #define PATH "cgiEnvSetting.sh"
#define PATH "text_sample"

static ssize_t	write_wrapper(int fd, const void* buf, size_t size);

int	main(int argc, char** argv, char** envp)
{
	int	fdset[2];
	int	pid;
	char	buf[1000000] = {'\0', };
	int		fileFd = open(PATH, O_RDONLY);
	struct stat	fileStatus;

	

	char**	envpTemp = envp;
	// while (*envpTemp != NULL)
	// {
	// 	std::cout << *envpTemp << '\n';
	// 	++envpTemp;
	// }

	ssize_t	count;
	std::string total_string = "";
	while ((count = read(fileFd, buf, 10)) > 0)
	{
		// std::cout << "output:" << buf << ", count:" << count << '\n';
		total_string = total_string + buf;
	}

	std::cout << "total line : " << std::endl << total_string << std::endl;


	stat(PATH, &fileStatus);
	static_cast<void>(argc);
	static_cast<void>(argv);
	pipe(fdset);
	pid = fork();
	if (pid == 0)
	{
		close(fdset[0]);
		dup2(fileFd, STDIN_FILENO);
		dup2(fdset[1], STDOUT_FILENO);
		exit(0);
		// execve("./cgi_tester", NULL, envp); //./cgi_tester
	}
	close(fdset[1]);

	// ssize_t	count;
	// std::string 
	total_string = "";
	while ((count = read(fdset[0], buf, 10)) > 0)
	{
		// std::cout << "output:" << buf << ", count:" << count << '\n';
		total_string = total_string + buf;
	}

	std::cout << "total line : " << std::endl << total_string << std::endl;

	close(fdset[0]);
	wait(NULL);
}
