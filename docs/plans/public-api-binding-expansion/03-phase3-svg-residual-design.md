# 03 Phase 3: SVG Residual Design

- 作成日: 2026-05-14
- 作業開始時刻: 2026-05-14 23:35:06 JST
- 対象台帳: `docs/plans/c-binding-remediation/checklists/public-api-svg-missing-triage.csv`

## 目的

Phase 3 で `SkSVGDOM` の load/render/query と `SkSVGCanvas::Make` を公開した後に残る SVG API の扱いを固定する。

## 現在の公開境界

実装済み:

- `SkSVGCanvas::Make`
- `SkSVGDOM::MakeFromStream`
- `SkSVGDOM::getRoot`
- `SkSVGDOM::setContainerSize`
- `SkSVGDOM::containerSize`
- `SkSVGDOM::findNodeById`
- `SkSVGDOM::render`
- `SkSVGNode::tag`
- `SkSVGDOM_renderNodeById` default-context helper
- `SkSVGNode_setAttributeString`

`SkSVGDOM` は owned `SkRefCnt` wrapper として扱う。`SkSVGNode` / `SkSVGSVG` は DOM が所有する borrowed opaque pointer であり、呼び出し側は release/delete しない。

## 残件カテゴリ

### A. renderNode/context ABI

対象:

- `SkSVGDOM::renderNode`
- `SkSVGSVG::renderNode`
- `SkSVGPresentationContext`
- `SkSVGRenderContext`
- `SkSVGLengthContext`

方針:

- `SkSVGDOM::renderNode` をそのまま C ABI 化するには `SkSVGPresentationContext` の wrapper が必要になる。
- Phase 3 では context を公開せず、`SkSVGDOM_renderNodeById(dom, canvas, id)` として default presentation context helper を公開した。
- full `SkSVGPresentationContext` ABI は、presentation inheritance、resource provider、font manager を明示する必要があるため後続へ残す。

### B. node read-only query

対象:

- covered: `SkSVGNode::tag`

方針:

- `findNodeById` の戻り値を C API から識別できるように、read-only query だけを先に公開する。
- enum は C ABI では `int32_t` として返す。NULL は `-1` を返す。
- node lifetime は引き続き DOM borrowed とし、node の ref/release は公開しない。
- `SkSVGNode::hasChildren` は generator 上は候補に見えるが、実ヘッダでは protected なので C ABI 対象外とする。

### C. node mutation / factory

対象:

- `SkSVGNode::appendChild`
- `SkSVGNode::setAttribute(SkSVGAttribute, const SkSVGValue&)`
- `SkSVGCircle::Make` など DOM node factory 群

方針:

- `SkSVGNode::setAttribute(const char*, const char*)` は `SkSVGNode_setAttributeString` として公開済み。
- DOM ownership、parent/child transfer、attribute value ABI が未確定のため Phase 3 では実装しない。
- 進める場合は `sk_sp<SkSVGNode>` owned wrapper と DOM append 時の ownership transfer を先に決める。

### D. SVG value/helper API

対象:

- `SkSVGLength`
- `SkSVGIRI`
- `SkSVGColor`
- `SkSVGPaint`
- `SkSVGFillRule`
- `SkSVGPresentationAttributes::MakeInitial`

方針:

- getter-only value wrapper は比較的安全だが、DOM mutation と併用しない限り単独価値が低い。
- `SkSVGNode::ComputeViewboxMatrix` は protected static helper なので C ABI 対象外とする。

### E. resource provider / image loading

対象:

- `SkSVGImage::LoadImage`
- `skresources::ResourceProvider` 連携

方針:

- skottie/skresources と同じ provider callback 規約が必要。
- Phase 5A の Callback / Resource Provider Foundation 後にまとめる。

## 次の実装候補

Phase 3 の残りとして進めるなら、順序は以下が妥当である。

1. full `SkSVGPresentationContext` ABI を Phase 3 外へ送る。
2. DOM node factory / mutation を Phase 3 から外す台帳整理を継続する。
3. `SkSVGValue` 系 value wrapper は DOM mutation フェーズまで保留する。

node factory、attribute mutation、resource provider は Phase 3 の範囲から外す。
