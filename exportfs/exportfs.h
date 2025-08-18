/*
 * exportfs.h - definitions for exporting file server
 */

#define DEBUG(...)
#define fidhash(s)	fhash[s%FHASHSIZE]

#define Proc	Exproc

typedef struct Fsrpc Fsrpc;
typedef struct Fid Fid;
typedef struct File File;
typedef struct Proc Proc;
typedef struct Qidtab Qidtab;

struct Fsrpc
{
	Fsrpc	*next;		/* freelist */
	int	flushtag;	/* Tag on which to reply to flush */
	Fcall	work;		/* Plan 9 incoming Fcall */
	uchar	buf[];		/* Data buffer */
};

struct Fid
{
	int	fid;		/* system fd for i/o */
	File	*f;		/* File attached to this fid */
	int	mode;
	int	nr;		/* fid number */
	int	mid;		/* Mount id */
	Fid	*next;		/* hash link */

	/* for preaddir -- ARRGH! */
	Dir	*dir;		/* buffer for reading directories */
	int	ndir;		/* number of entries in dir */
	int	cdir;		/* number of consumed entries in dir */
	int	gdir;		/* glue index */
	vlong	offset;		/* offset in virtual directory */
};

struct File
{
	char	*name;
	int	ref;
	Qid	qid;
	Qidtab	*qidt;
	int	inval;
	File	*parent;
	File	*child;
	File	*childlist;
};

struct Proc
{
	Lock	lock;
	Fsrpc	*busy;
	Proc	*next;
	void	*kp;
};

struct Qidtab
{
	int	ref;
	int	type;
	int	dev;
	vlong	path;
	vlong	uniqpath;
	Qidtab	*next;
};

enum
{
	FHASHSIZE	= 64,
	Fidchunk	= 1000,
	Npsmpt		= 32,
	Nqidbits		= 5,
	Nqidtab		= (1<<Nqidbits),
};

#define Enomem Exenomem
#define Ebadfid Exebadfid
#define Enotdir Exenotdir
#define Edupfid Exedupfid
#define Eopen Exeopen
#define Exmnt Exexmnt

extern char Enomem[];
extern char Ebadfid[];
extern char Enotdir[];
extern char Edupfid[];
extern char Eopen[];
extern char Exmnt[];

Extern File	*root;
Extern File	*psmpt;
Extern Fid	**fhash;
Extern Fid	*fidfree;
Extern Proc	*Proclist;
Extern Qidtab	*qidtab[Nqidtab];
Extern ulong	messagesize;

/* File system protocol service procedures */
void Xattach(Fsrpc*);
void Xauth(Fsrpc*);
void Xclunk(Fsrpc*); 
void Xcreate(Fsrpc*);
void Xflush(Fsrpc*); 
void Xnop(Fsrpc*);
void Xremove(Fsrpc*);
void Xstat(Fsrpc*);
void Xversion(Fsrpc*);
void Xwalk(Fsrpc*);
void Xwstat(Fsrpc*);
void slave(Fsrpc*);

void	io(int, int);
void	reply(Fcall*, Fcall*, char*);
void	mounterror(char*);

Fid 	*getfid(int);
int	freefid(int);
Fid	*newfid(int);
Fsrpc	*getsbuf(void);
void	putsbuf(Fsrpc*);
void	initroot(void);
void	fatal(char*, ...);
char*	makepath(File*, char*);
File	*file(File*, char*);
void	freefile(File*);
void	slaveopen(Fsrpc*);
void	slaveread(Fsrpc*);
void	slavewrite(Fsrpc*);
void	blockingslave(void*);
void	reopen(Fid *f);
void	noteproc(int, char*);
void	flushaction(void*, char*);
void	pushfcall(char*);
Qidtab* uniqueqid(Dir*);
void	freeqid(Qidtab*);
char*	estrdup(char*);
void*	emallocz(uint);
int	readmessage(int, char*, int);
