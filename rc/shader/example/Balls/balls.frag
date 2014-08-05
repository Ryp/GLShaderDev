
// Bulb Spill by eiffie (SoC with reflections sample)
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
varying vec2 coord;

uniform float time;
uniform uvec2 screenSize;

float focalDistance=2.0,aperture=0.03,fudgeFactor=0.8,shadowCone=0.5;
vec3 L;//light direction
float hash(float n) {return fract(sin(n) * 43758.5453123);}//from iq

float DE(in vec3 z0){
	vec3 z=z0+vec3(0.0,1.8,0.0);
	vec2 v=floor(z.xz);
	float h=hash(v.x+v.y*117.0);
	z.y-=abs(sin(time*7.0+h*6.283))*0.5;
	z.xz=fract(z.xz)-0.5+sin(v*2.0+v.yx)*0.1;
	float d=length(z)-0.2;
	z=z0+vec3(0.5,1.8,0.5);
	vec2 v2=floor(z.xz);
	h=hash(v2.x+v2.y*117.0+33.0);
	z.y-=abs(sin(time*7.0+h*6.283))*0.5;
	z.xz=fract(z.xz)-0.5+sin(v2+v2.yx*2.0)*0.1;
	float d2=length(z)-0.2;
	float d3=z0.y+2.0;
	return min(d,min(d2,d3));
}

vec4 CE(in vec3 z0, inout vec3 norm){
	vec4 col;
	vec3 z=z0+vec3(0.0,1.8,0.0);
	vec2 v=floor(z.xz);
	float h=hash(v.x+v.y*117.0);
	z.y-=abs(sin(time*7.0+h*6.283))*0.5;
	z.xz=fract(z.xz)-0.5+sin(v*2.0+v.yx)*0.1;
	float d=length(z)-0.2;
	vec3 n1=z;
	z=z0+vec3(0.5,1.8,0.5);
	vec2 v2=floor(z.xz);
	h=hash(v2.x+v2.y*117.0+33.0);
	z.y-=abs(sin(time*7.0+h*6.283))*0.5;
	z.xz=fract(z.xz)-0.5+sin(v2+v2.yx*2.0)*0.1;
	float d2=length(z)-0.2;
	float d3=z0.y+2.0;
	
	if(d<d2 && d<d3){col=vec4(1.0,0.5+sin(v)*0.5,0.6);norm=normalize(n1);}
	else if(d2<d3){col=vec4(0.5+sin(v2)*0.5,0.0,0.6);norm=normalize(z);}
	else {col=vec4(0.1,0.3,0.2,0.2);norm=vec3(0.0,1.0,0.0);}
	return col;
}

float pixelSize;
float CircleOfConfusion(float t){//calculates the radius of the circle of confusion at length t
	return max(abs(focalDistance-t)*aperture,pixelSize*(1.0+t));
}

mat3 lookat(vec3 fw,vec3 up){
	fw=normalize(fw);vec3 rt=normalize(cross(fw,normalize(up)));return mat3(rt,cross(rt,fw),fw);
}
float linstep(float a, float b, float t){return clamp((t-a)/(b-a),0.,1.);}// i got this from knighty and/or darkbeam
//random seed and generator
float randSeed=fract(cos((gl_FragCoord.x+gl_FragCoord.y*117.0+time*10.0)*473.7192451));
float randStep(){//a simple pseudo random number generator based on iq's hash
	return  (0.8+0.2*fract(sin(++randSeed)*43758.5453123));
}

vec3 Background(vec3 rd){return vec3(0.0);}
vec3 FuzzyReflection(vec3 ro, vec3 rd, float coneGrad, float rCoC){
	float t=0.0,d=1.0;
	ro+=rd*rCoC*2.0;
	vec4 col=vec4(0.0);
	for(int i=0;i<8;i++){
		float r=rCoC+t*coneGrad;//radius of cone
		d=DE(ro+rd*t)+0.5*r;
		if(d<r){
			vec3 p=ro+rd*(t+d-0.51*r),N;
			vec4 mcol=CE(p,N);
			vec3 scol=mcol.rgb*(0.5+dot(N,L)*0.5);//do some fast light calcs (you can forget about shadow casting, too expensive)
			float alpha=(1.0-col.w)* linstep(-r,r,-d);//calculate the mix like cloud density
			col+=vec4(scol*alpha,alpha);//blend in the new color
		}
		t+=max(d,pixelSize)*randStep();
	}
	return col.rgb+Background(rd)*(1.0-clamp(col.w,0.0,1.0));
}

void main()
{
	pixelSize=2.0/screenSize.y;
	float tim=time*1.5;
	vec3 ro=vec3(tim*2.0,0.0,tim);
	vec3 rd=lookat(vec3(2.0,-1.0,0.0),vec3(0.0,1.0,0.0))*normalize(vec3((2.0*gl_FragCoord.xy-screenSize.xy)/screenSize.y,2.0));
	const vec3 lightColor=vec3(1.0,0.5,0.25);
	L=normalize(vec3(-0.5,-0.6,-0.4));
	vec4 col=vec4(0.0);//color accumulator
	float t=0.0;//distance traveled, minimum light distance
	for(int i=1;i<48;i++){//march loop
		if(col.w>0.9 || t>20.0)continue;//bail if we hit a surface or go out of bounds
		float rCoC=CircleOfConfusion(t);//calc the radius of CoC
		float d=DE(ro)+0.5*rCoC;
		if(d<rCoC){//if we are inside add its contribution
			vec3 p=ro+rd*(d-0.51*rCoC),N;//back up 
			vec4 mcol=CE(p,N);
			float refl=mcol.a;
			vec3 scol=mcol.rgb*(0.5+0.5*dot(N,L));
			scol+=pow(max(0.0,dot(reflect(rd,N),L)),4.0)*lightColor;
			//scol*=FuzzyShadow(p,L,1.0,shadowCone,rCoC);	
			scol=scol*(1.0-refl)+refl*FuzzyReflection(p,reflect(rd,N),refl,rCoC);
			float alpha=fudgeFactor*(1.0-col.w)*linstep(-rCoC,rCoC,-d);//calculate the mix like cloud density
			col+=vec4(scol*alpha,alpha);//blend in the new color	
			float k=dot(N,-rd);
			if(k>0.0)d+=rCoC*0.5*(1.0-k);	//extra speedup around the edges :)	
		}
		d=fudgeFactor*max(d,pixelSize)*randStep();//add in noise to reduce banding and create fuzz
		ro+=d*rd;//march
		t+=d;
	}//mix in background color
	col.w*=clamp(1.0-t/20.0,0.0,1.0);//fade out to background color
	col.rgb=mix(Background(rd),col.rgb,clamp(col.w,0.0,1.0));

	gl_FragColor = vec4(clamp(col.rgb*2.0,0.0,1.0),1.0);
}
