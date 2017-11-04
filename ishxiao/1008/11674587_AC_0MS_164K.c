#include <stdio.h>
#include <string.h>

typedef enum _HaabMonth{
	//00-09
	pop,no,zip,zotz,tzec,xul,yoxkin,mol,chen,yax,
	//10-17
	zac,ceh,mac,kankin,muan,pax,koyab,cumhu,
	//18
	uayet,
} HaabMonth;

char HaabMonthText[19][7]=
{
	//00-09
	"pop","no","zip","zotz","tzec","xul","yoxkin","mol","chen","yax",
	//10-17
	"zac","ceh","mac","kankin","muan","pax","koyab","cumhu",
	//18
	"uayet",
};

typedef struct _HaabDate{
	int Day;
	HaabMonth Month;
	char strMonth[7];
	int year;
} HaabDate;

typedef enum{
	//00-09
	imix,ik,akbal,kan,chicchan,cimi,manik,lamat,muluk,ok,
	//10-19
	chuen,eb,ben,ix,mem,cib,caban,eznab,canac,ahau,
} hollyDay;

char hollyDayText[20][9]=
{
	//00-09
	"imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok",
	//10-19
	"chuen","eb","ben","ix","mem","cib","caban","eznab","canac","ahau",
};

typedef struct _hollyDate{
	int period;
	hollyDay Day;
	char strDay[9];
	int year;
} hollyDate;

hollyDate HaabDate2hollyDate(HaabDate stHaabDate)
{
	hollyDate sthollyDate;
	int iOrdNum;
	//
	if(stHaabDate.strMonth != NULL)
		iOrdNum = stHaabDate.Day+ 20 * HaabMonthText2Month(stHaabDate.strMonth) + 365 * stHaabDate.year;
	else
		iOrdNum = stHaabDate.Day+ 20 * stHaabDate.Month + 365 * stHaabDate.year;
	sthollyDate.period = (iOrdNum%260)%13 + 1;
	sthollyDate.Day = (hollyDay) ((iOrdNum%260)%20);
	strcpy(sthollyDate.strDay,hollyDayText[sthollyDate.Day]);
	sthollyDate.year = iOrdNum/260;

	return sthollyDate;
}
HaabMonth HaabMonthText2Month(const char *strMonth)
{
	HaabMonth enHaabMonth = pop;

	while(enHaabMonth <= uayet)
	{
		if(0 == strcmp(strMonth,HaabMonthText[enHaabMonth]))
			break;
		else if(enHaabMonth < uayet)
			enHaabMonth = (HaabMonth) (enHaabMonth +1);
		else
			break;
	}

	return enHaabMonth;
}

int main()
{
	int iInNum = 0;
	int i = 0;
	HaabDate* stHaabDate;
	hollyDate* sthollyDate;

	scanf("%d",&iInNum);

	stHaabDate  = (HaabDate*) calloc(iInNum, sizeof(HaabDate));
	sthollyDate = (hollyDate*)calloc(iInNum, sizeof(hollyDate));

	for(i = 0; i < iInNum; i++)
	{
		scanf("%d.%s %d",&stHaabDate[i].Day,&stHaabDate[i].strMonth,&stHaabDate[i].year);
		sthollyDate[i] = HaabDate2hollyDate(stHaabDate[i]);
	}

	printf("%d\n",iInNum);
	for(i = 0; i < iInNum; i++)
	{
		printf("%d %s %d\n", sthollyDate[i].period,sthollyDate[i].strDay,sthollyDate[i].year);
	}

	free(stHaabDate);
	free(sthollyDate);

	return 0;
}