import React, { useRef, useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import bg from '../assets/background/background.png';
import logo from '../assets/logo/page_title/logo_gribouillit.png';

import brushIcon from '../assets/logo/canva tools/brush.png';
import eraserIcon from '../assets/logo/canva tools/eraser.png';
import lineIcon from '../assets/logo/canva tools/line.png';
import circleIcon from '../assets/logo/canva tools/circle.png';
import squareIcon from '../assets/logo/canva tools/square.png';

import { postService } from '../services/postService';

export default function DrawPage() {
  const canvasRef = useRef(null);
  const ctxRef = useRef(null);
  const navigate = useNavigate();

  const [drawing, setDrawing] = useState(false);
  const [tool, setTool] = useState('brush');
  const [color, setColor] = useState('#000000');
  const [size, setSize] = useState(5);
  const [startPos, setStartPos] = useState(null);
  const [description, setDescription] = useState('');
  const [publishing, setPublishing] = useState(false);
  const [error, setError] = useState(null);

  const COLORS = [
    '#8B5CF6', '#F97316', '#22C55E', '#EC4899', '#3B82F6',
    '#FACC15', '#10B981', '#000000', '#FFFFFF', '#8B4513'
  ];

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    ctx.fillStyle = 'white';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.lineCap = 'round';
    ctx.lineJoin = 'round';
    ctx.strokeStyle = color;
    ctx.lineWidth = size;
    ctxRef.current = ctx;
  }, []);

  useEffect(() => {
    if (!ctxRef.current) return;
    ctxRef.current.strokeStyle = tool === 'eraser' ? '#FFFFFF' : color;
    ctxRef.current.lineWidth = size;
  }, [color, size, tool]);

  const getMousePos = (e) => {
    const rect = canvasRef.current.getBoundingClientRect();
    return { x: e.clientX - rect.left, y: e.clientY - rect.top };
  };

  const startDrawing = (e) => {
    const pos = getMousePos(e);
    setDrawing(true);
    setStartPos(pos);
    if (tool === 'brush' || tool === 'eraser') {
      ctxRef.current.beginPath();
      ctxRef.current.moveTo(pos.x, pos.y);
    }
  };

  const draw = (e) => {
    if (!drawing) return;
    const pos = getMousePos(e);
    if (tool === 'brush' || tool === 'eraser') {
      ctxRef.current.lineTo(pos.x, pos.y);
      ctxRef.current.stroke();
    }
  };

  const stopDrawing = (e) => {
    if (!drawing) return;
    const pos = getMousePos(e);
    const ctx = ctxRef.current;
    if (tool === 'line') {
      ctx.beginPath();
      ctx.moveTo(startPos.x, startPos.y);
      ctx.lineTo(pos.x, pos.y);
      ctx.stroke();
    }
    if (tool === 'rect') {
      ctx.strokeRect(startPos.x, startPos.y, pos.x - startPos.x, pos.y - startPos.y);
    }
    if (tool === 'circle') {
      const radius = Math.sqrt(Math.pow(pos.x - startPos.x, 2) + Math.pow(pos.y - startPos.y, 2));
      ctx.beginPath();
      ctx.arc(startPos.x, startPos.y, radius, 0, 2 * Math.PI);
      ctx.stroke();
    }
    ctx.closePath();
    setDrawing(false);
  };

  const isCanvasBlank = () => {
    const canvas = canvasRef.current;
    if (!canvas) return true;
    const ctx = canvas.getContext('2d');
    const { data } = ctx.getImageData(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < data.length; i += 4) {
      if (data[i] !== 255 || data[i+1] !== 255 || data[i+2] !== 255) return false;
    }
    return true;
  };

  const handlePublish = async () => {
    setError(null);
    if (isCanvasBlank()) {
      setError('Le canvas est vide. Dessine quelque chose avant de publier !');
      return;
    }
    setPublishing(true);
    try {
      const imageData = canvasRef.current.toDataURL('image/png');
      await postService.create(imageData, description);
      navigate('/home');
    } catch (err) {
      console.error('Publish error:', err);
      setError('Erreur lors de la publication. Reessaie !');
    } finally {
      setPublishing(false);
    }
  };

  const FONT = 'Gribouillit2.0, sans-serif';

  return (
    <div style={{
      minHeight: '100vh',
      backgroundImage: `url(${bg})`,
      backgroundSize: 'cover',
      display: 'flex',
      alignItems: 'center',
      justifyContent: 'center',
      padding: '2rem',
      fontFamily: FONT
    }}>
      <div style={{
        width: '1000px',
        background: 'white',
        border: '4px solid black',
        padding: '2rem',
        borderRadius: '4px'
      }}>
        {/* HEADER */}
        <div style={{ textAlign: 'center', marginBottom: '1rem', borderBottom: '2px solid black', paddingBottom: '1rem' }}>
          <img src={logo} alt="Gribouillit" style={{ maxHeight: '120px' }} />
          <h1 style={{ fontSize: '2rem', color: '#000', margin: '0.5rem 0 0' }}>
            Cree ta publication
          </h1>
        </div>

        {/* DESCRIPTION */}
        <div style={{ marginBottom: '1rem' }}>
          <input
            type="text"
            value={description}
            onChange={(e) => setDescription(e.target.value)}
            placeholder="Ajoute une description (optionnel)..."
            maxLength={200}
            style={{
              width: '100%',
              padding: '0.6rem 1rem',
              fontSize: '1rem',
              fontFamily: FONT,
              border: '2px solid black',
              borderRadius: '4px',
              outline: 'none',
              boxSizing: 'border-box'
            }}
          />
        </div>

        {/* CANVAS */}
        <div style={{ display: 'flex', justifyContent: 'center', marginBottom: '1.5rem' }}>
          <canvas
            ref={canvasRef}
            width={600}
            height={500}
            style={{ width: '600px', height: '500px', border: '3px solid black', cursor: 'crosshair', backgroundColor: 'white' }}
            onMouseDown={startDrawing}
            onMouseMove={draw}
            onMouseUp={stopDrawing}
            onMouseLeave={stopDrawing}
          />
        </div>

        {/* TOOLS ROW */}
        <div style={{ display: 'flex', gap: '3rem', justifyContent: 'center', alignItems: 'flex-start', marginBottom: '1.5rem' }}>
          {/* COLORS */}
          <div style={{ display: 'grid', gridTemplateColumns: 'repeat(5, 48px)', gap: '8px' }}>
            {COLORS.map((c, i) => (
              <div key={i} onClick={() => setColor(c)} style={{
                width: '48px', height: '48px', backgroundColor: c,
                border: color === c && tool !== 'eraser' ? '4px solid #00FEE5' : '2px solid black',
                cursor: 'pointer', borderRadius: '4px'
              }} />
            ))}
          </div>

          {/* TOOL BUTTONS + SIZE */}
          <div style={{ display: 'flex', flexDirection: 'column', gap: '1rem', alignItems: 'center' }}>
            <div style={{ display: 'flex', gap: '0.5rem' }}>
              {[
                { id: 'brush', icon: brushIcon, label: 'Pinceau' },
                { id: 'eraser', icon: eraserIcon, label: 'Gomme' },
                { id: 'line', icon: lineIcon, label: 'Ligne' },
                { id: 'rect', icon: squareIcon, label: 'Rectangle' },
                { id: 'circle', icon: circleIcon, label: 'Cercle' },
              ].map(({ id, icon, label }) => (
                <button key={id} onClick={() => setTool(id)} title={label} style={{
                  width: '56px', height: '56px',
                  border: tool === id ? '4px solid #00FEE5' : '2px solid black',
                  borderRadius: '4px', cursor: 'pointer',
                  display: 'flex', alignItems: 'center', justifyContent: 'center',
                  backgroundColor: 'white'
                }}>
                  <img src={icon} alt={label} style={{ width: '36px', height: '36px' }} />
                </button>
              ))}
            </div>

            <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', gap: '4px' }}>
              <label style={{ fontWeight: 'bold', fontSize: '0.9rem', fontFamily: FONT }}>Taille</label>
              <input type="range" min="1" max="30" value={size} onChange={(e) => setSize(e.target.value)} style={{ width: '120px' }} />
              <span style={{ fontSize: '0.85rem', fontFamily: FONT }}>{size}px</span>
            </div>
          </div>
        </div>

        {/* ERROR */}
        {error && (
          <p style={{ color: '#dc2626', textAlign: 'center', fontFamily: FONT, marginBottom: '0.75rem' }}>
            ⚠️ {error}
          </p>
        )}

        {/* ACTIONS */}
        <div style={{ display: 'flex', gap: '1rem', justifyContent: 'center' }}>
          <button
            onClick={() => navigate('/home')}
            style={{
              padding: '0.75rem 2rem', fontSize: '1rem', fontFamily: FONT,
              backgroundColor: 'white', border: '2px solid black',
              borderRadius: '4px', cursor: 'pointer', fontWeight: 'bold', color: '#000'
            }}
          >
            Annuler
          </button>
          <button
            onClick={handlePublish}
            disabled={publishing}
            style={{
              padding: '0.75rem 2.5rem', fontSize: '1rem', fontFamily: FONT,
              backgroundColor: publishing ? '#555' : '#B5FF6B',
              border: '2px solid black', borderRadius: '4px',
              cursor: publishing ? 'not-allowed' : 'pointer',
              fontWeight: 'bold', color: '#000'
            }}
          >
            {publishing ? 'Publication...' : '🎨 Publier !'}
          </button>
        </div>
      </div>
    </div>
  );
}
